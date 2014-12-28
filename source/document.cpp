#include <cassert>
#include <fstream>

#include <stdio.h>

#include "document.hpp"
#include "element_array.hpp"
#include "element_boolean.hpp"
#include "element_null.hpp"
#include "element_object.hpp"
#include "cJSON/cJSON.h"

namespace JVJSON_NAMESPACE_NAME
{

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
    return this->undefinedElement;
}

bool_t Document::ReadFromFile(const char* filename, const char* schemaFilename)
{
    printf("Parsing file %s\n", filename);
    
    std::ifstream infile;
    infile.open(filename);
    
    if (!infile.is_open())
    {
        return false;
    }
    
    infile.seekg(0, std::ios::end);
    
    size_t size = infile.tellg();
    char* buffer = new char[size];
    
    infile.seekg(0);
    infile.read(&buffer[0], size);    
    
    cJSON *root = cJSON_Parse(buffer);
    
    printf("Parsed file, root pointer 0x%x\n", (uint32_t)root);
    
    delete buffer;
    
    this->rootElement = this->RecursiveParseCjsonItems(root);
    
    // Allocate storage for the Element values.
    this->AllocateValueTable();
    
    // Go through the cJSON items and set the Element values.    
       
    cJSON_Delete(root);
    
    return true;
}   

Document::Iterator Document::Begin(void)
{   
    return Document::Iterator(this, &this->GetRootElement());
}

Document::Iterator Document::End(void)
{   
    return Document::Iterator(this, &this->GetUndefinedElement());
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
            newElement = new ElementBoolean();
            break;
        case cJSON_True:
            newElement = new ElementBoolean();
            break;
        case cJSON_NULL:
            newElement = new ElementNull();
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
    }
        
    return newElement;
}

void Document::AllocateValueTable(void)
{
    return;
}

Document::Iterator::Iterator(Document* document, Element* initialElement)
{
    this->document = document;
    this->element = initialElement;
    this->containerIterators = std::deque<Element::Iterator>();
}

Document::Iterator& Document::Iterator::Next(void)
{
    if (this->element->GetSize())
    {
        Element::Iterator iterator = this->element->Begin();
        this->containerIterators.push_front(iterator);
        this->element = &iterator.GetElement();
    }
    else
    {
        while (this->containerIterators.size())
        {
            Element::Iterator iterator = this->containerIterators[0]++;
            if (iterator == this->containerIterators[0].End())
            {
                this->containerIterators.pop_front();
            }
            else
            {
                this->element = &iterator.GetElement();
                break;
            }
        }
    }
    
    // If we get here, we hit the end...
    if (!this->containerIterators.size())
    {
        this->element = &this->document->GetUndefinedElement();
    }
    
    return *this;
}

bool_t Document::Iterator::operator==(const Iterator& other)
{
    return (this->element == other.element);
}

bool_t Document::Iterator::operator!=(const Iterator& other)
{
    return (this->element != other.element);
}
    
}
