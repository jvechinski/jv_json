//////////////////////////////////////////////////////////////////////
/// @file
///
/// Implementation of the JSON Document class.  
///
/// Part of the JV JSON parser project, 
/// https://github.com/jvechinski/jv_json
/// Released under the MIT license.
///
/// @ingroup jv_json
///
/// Copyright (c) 2015 Jeremy S. Vechinski
///
/// Permission is hereby granted, free of charge, to any person 
/// obtaining a copy of this software and associated documentation 
/// files (the "Software"), to deal in the Software without restriction, 
/// including without limitation the rights to use, copy, modify, merge, 
/// publish, distribute, sublicense, and/or sell copies of the Software, 
/// and to permit persons to whom the Software is furnished to do so, 
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be 
/// included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
/// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
/// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS 
/// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
/// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
/// SOFTWARE.
//////////////////////////////////////////////////////////////////////


#include <cassert>
#include <cstring>
#include <fstream>
#include <sstream>

#include <stdio.h>

#include "document.hpp"
#include "element_array.hpp"
#include "element_boolean.hpp"
#include "element_float.hpp"
#include "element_integer.hpp"
#include "element_null.hpp"
#include "element_object.hpp"
#include "element_reference.hpp"
#include "element_string.hpp"
#include "cJSON/cJSON.h"

namespace JVJSON_NAMESPACE_NAME
{
    
Element undefinedElement;

std::string Document::GetFilename(void)
{
    return this->filename;
}

Element& Document::GetRootElement(void)
{
    if (this->rootElement)
    {
        return *this->rootElement;
    }
    else
    {
        return this->GetUndefinedElement();
    }
}

Element& Document::GetUndefinedElement(void)
{
    return undefinedElement;
}

Element* Document::InternalReadFromJsonFile(std::string filename) 
{
    std::ifstream infile;
    infile.open(filename.c_str());
    
    if (!infile.is_open())
    {
        return nullptr;
    }
    
    infile.seekg(0, std::ios::end);
    
    size_t size = infile.tellg();
    char* buffer = new char[size];
    
    infile.seekg(0);
    infile.read(&buffer[0], size);    
    
    cJSON *root = cJSON_Parse(buffer);
    
    delete buffer;
    
    Element* rootElement = this->RecursiveParseCjsonItems(root);
       
    cJSON_Delete(root);
    
    return rootElement;
}

bool_t Document::ReadFromFile(const char* filename, const char* schemaFilename)
{
    bool_t returnValue = true;
    
    this->filename = std::string(filename);
    
    if (schemaFilename)
    {
        this->schemaFilename = std::string(schemaFilename);
        
        this->schemaDocument = new Document();
        
        returnValue = this->schemaDocument->ReadFromFile(
            schemaFilename);
    }       
    
    this->rootElement = InternalReadFromJsonFile(this->filename);
    
    if (!this->rootElement)
    {
        returnValue = false;
    }
    
    if ((returnValue) && (schemaFilename))
    {
        returnValue = this->PairWithSchemaElements();
        returnValue = this->ValidateAgainstSchema();
    }
    
    this->HandleJsonReferences();
    
    return returnValue;
}   

Element* Document::RecursiveParseCjsonItems(cJSON* item)
{
    //printf("RecursiveParseCjsonItems, type %d\n", item->type);
    
    // Turn the cJSON item into an Element object.
    Element* newElement = ConstructElementFromCjsonItem(item);
    
    // Assert that the parsing was successful.
    //assert(newElement != nullptr);
    if (newElement == nullptr)
    {
        return newElement;
    }
    
    // Special case... for arrays and objects we need to parse the
    // children.
    if (newElement->GetType() == ELEMENT_TYPE_ARRAY)
    {
        // Loop through the children.
        cJSON* childItem = item->child;
        std::size_t index = 0;
        while (childItem)
        {
            Element* childElement = RecursiveParseCjsonItems(childItem);
            if (childElement)
            {
                newElement->AddElement(index, *childElement);
            }
            childItem = childItem->next;
            index += 1;
        }        
    }
    else if (newElement->GetType() == ELEMENT_TYPE_OBJECT)
    {
        // Loop through the children.
        cJSON* childItem = item->child;
        while (childItem)
        {
            Element* childElement = RecursiveParseCjsonItems(childItem);
            if (childElement)
            {
                newElement->AddElement(childItem->string, *childElement);
            }
            childItem = childItem->next;
        }
    }
        
    return newElement;
}

Element* Document::ConstructElementFromCjsonItem(cJSON* item)
{
    Element* newElement = nullptr;
    
    switch (item->type)
    {
        case cJSON_False:
            newElement = new ElementBoolean(false);
            break;
        case cJSON_True:
            newElement = new ElementBoolean(true);
            break;
        case cJSON_NULL:
            newElement = new ElementNull();
            break;
        case cJSON_Number:
            // We use the presence of a decimal point (i.e. 1.0, 1.1)
            // or exponent (1e-10, 2E31) to signify a floating point
            // number.
            // Any number without this identifying information is
            // considered an integer.  (Note that the JSON standard
            // does not make this distinction, but this is how
            // many languages where floating point numbers and integers
            // are different handle things.)
            if (item->valuefractional)
            {
                newElement = new ElementFloat((floatmax_t)item->valuedouble);
            }
            else
            {
                newElement = new ElementInteger((intmax_t)item->valueint);                
            }
            break;
        case cJSON_String:
            newElement = new ElementString(item->valuestring);
            break;
        case cJSON_Object:
            newElement = new ElementObject();
            break;
        case cJSON_Array:
            newElement = new ElementArray();
            break;        
    }
    
    if (newElement != nullptr)
    {
        newElement->document = this;
        newElement->schemaElement = nullptr;
    }
        
    return newElement;
}

bool_t Document::ValidateAgainstSchema(bool_t raiseException)
{
    bool_t returnValue = true;
    Document::Iterator i = this->Begin();
    
    while ((i != this->End()) && (returnValue))
    {
        returnValue = i.GetElement().ValidateAgainstSchema(
            raiseException);
        i++;
    }
    
    return returnValue;
}

bool_t Document::PairWithSchemaElements(void)
{
    Element* schemaRootElement = nullptr;
    
    if (this->schemaDocument)
    {        
        schemaRootElement = &(this->schemaDocument->GetRootElement());        
        
        if ((this->rootElement) && (schemaRootElement))
        {
            this->rootElement->schemaElement = schemaRootElement;
            this->rootElement->AssignSchemasToChildElements();
        }
    }
    
    return true;
}

void Document::HandleJsonReferences(void)
{
    Document::Iterator i = this->Begin();
    
    while (i != this->End())
    {
        // Looking for an object with a string member named 
        // $ref.  This special combination signifies a JSON
        // reference.  If this is found, we create a JSON reference
        // element to replace the object.
        Element& element = i.GetElement();
        if (
            (element.GetType() == ELEMENT_TYPE_OBJECT) &&
            (element.HasElement("$ref")) &&
            (element.GetElement("$ref").GetType() == ELEMENT_TYPE_STRING)
           )
        {
            ElementReference* referenceElement = new ElementReference(
                element.GetElement("$ref").GetValueAsString(),
                this);
                
            if (element.parentElement != nullptr)
            {
                element.parentElement->ReplaceElement(element, *referenceElement);
            }
        }
        
        i++;
    }
}

bool_t Document::HasElement(const std::string& elementName)
{
    bool_t elementExists = false;
    
    this->GetElement(elementName, &elementExists);
    
    return elementExists;
}

bool_t Document::HasElement(const uint32_t elementIndex)
{
    bool_t elementExists = false;
    
    this->GetElement(elementIndex, &elementExists);
    
    return elementExists;
}

static bool_t StringStartsWith(const std::string& s1, const std::string& s2) 
{
    return (s2.size() <= s1.size() && s1.compare(0, s2.size(), s2) == 0);
}
    
Element& Document::GetElement(const std::string& elementName, bool_t* exists)
{
    // Are they referencing an element in this document using 
    // a path / URI?    
    if (StringStartsWith(elementName, "#/"))
    {
        return this->GetElementByPath(elementName, exists);
    }
    
    if (this->rootElement != nullptr)
    {
        return this->rootElement->GetElement(elementName, exists);
    }
    else
    {
        if (exists != nullptr)
        {
            *exists = false;
        }
    }
    
    return this->GetUndefinedElement();
}

Element& Document::GetElement(const uint32_t elementIndex, bool_t* exists)
{
    if (this->rootElement != nullptr)
    {
        return this->rootElement->GetElement(elementIndex, exists);
    }

    if (exists != nullptr)
    {
        *exists = false;
    }
    
    return this->GetUndefinedElement();
}

void StringSplit(std::vector<std::string>& pieces, const std::string& stringToSplit, char delimiter) 
{
    std::stringstream ss(stringToSplit); 
    std::string piece;
  
    while (std::getline(ss, piece, delimiter)) 
    {
        pieces.push_back(piece);
    }
}

Element& Document::GetElementByPath(const std::string& path, bool_t* exists)
{
    std::vector<std::string> pathParts;
        
    if (exists != nullptr)
    {
        *exists = false;
    }
    
    StringSplit(pathParts, path, '/');
    
    if (pathParts.size() >= 1)
    {
        Element* currentElement = &this->GetRootElement();
        pathParts.erase(pathParts.begin());
        
        while (pathParts.size())
        {
            bool_t nextElementExists;
            Element& nextElement = currentElement->GetElement(pathParts[0], &nextElementExists);
            
            if (!nextElementExists)
            {
                return this->GetUndefinedElement();    
            }
            
            pathParts.erase(pathParts.begin());
            currentElement = &nextElement;
        }
        
        if (exists != nullptr)
        {
            *exists = true;
        }
        
        return *currentElement;
    }

    return this->GetUndefinedElement();    
}
    
}
