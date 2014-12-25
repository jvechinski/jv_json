#include <cassert>
#include <fstream>

#include "document.hpp"
#include "element_object.hpp"
#include "element_boolean.hpp"
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
    return Document::Iterator(&this->GetRootElement());
}

Document::Iterator Document::End(void)
{   
    return Document::Iterator(&this->GetUndefinedElement());
}

Element* Document::RecursiveParseCjsonItems(cJSON* item)
{
    // Turn the cJSON item into an Element object.
    Element* newElement = ConstructElementFromCjsonItem(item);
    
    // Assert that the parsing was successful.
    assert(newElement != nullptr);
    
    // Special case... for arrays and objects we need to parse the
    // children.
    if (newElement->GetType() == ELEMENT_TYPE_ARRAY)
    {
        
    }
    else if (newElement->GetType() == ELEMENT_TYPE_OBJECT)
    {
        // Loop through the children.
        cJSON* childItem = item->child;
        while (childItem)
        {
            Element* childElement = ConstructElementFromCjsonItem(childItem);
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
        case cJSON_Object:
            newElement = new ElementObject();
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

Document::Iterator::Iterator(Element* initialElement)
{
    this->element = initialElement;
    this->containerIterators = std::deque<Element::Iterator>();
}

Document::Iterator& Document::Iterator::Next(void)
{
    if (
        (this->element->GetType() == ELEMENT_TYPE_ARRAY) ||
        (this->element->GetType() == ELEMENT_TYPE_OBJECT)
       )
    {
        
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
