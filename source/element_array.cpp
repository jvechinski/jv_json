#include <stdio.h>
#include <cstdlib>

#include "element_array.hpp"
#include "document.hpp"
#include "exception.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
ElementType ElementArray::GetType(void) const
{
    return ELEMENT_TYPE_ARRAY;
}

bool_t ElementArray::IsContainer(void) const
{
    return true;
}    

Element& ElementArray::GetElementPrivate(const std::string& elementName, bool_t* exists)
{
    // Call parent class GetElementPrivate() to handle any common
    // cases (i.e. $schema).
    Element& e = Element::GetElementPrivate(elementName, exists);
    
    if (*exists)
    {
        return e;
    }
    
    // See if we can convert the string into an integer, then use
    // the integer to look up by index.
    const char_t* beginPointer = elementName.c_str();
    char_t* endPointer = (char_t*)beginPointer;
    std::size_t elementIndex = strtoul(beginPointer, &endPointer, 0);
    if (beginPointer != endPointer)
    {
        // If the array is large enough to contain the element...
        if (elementIndex < this->GetSize())
        {
            *exists = true;
            return *this->array[elementIndex];
        }
    }
    
    // e should be set to the value provided by the parent class
    // GetElementPrivate(), i.e. undefined.
    return e;
}
    
Element& ElementArray::GetElementPrivate(const uint32_t elementIndex, bool_t* exists)
{
    // Call parent class GetElementPrivate() to handle any common
    // cases.
    Element& e = Element::GetElementPrivate(elementIndex, exists);
    
    if (*exists)
    {        
        return e;
    }
    
    // If the array is large enough to contain the element...
    if (elementIndex < this->GetSize())
    {
        *exists = true;
        return *this->array[elementIndex];
    }
    
    // e should be set to the value provided by the parent class
    // GetElementPrivate(), i.e. undefined.
    return e;
}

void ElementArray::AddElement(const uint32_t elementIndex, Element& element)
{
    // Call the parent class AddElement() function, which performs
    // common add behavior.
    Element::AddElement(element);
    
    // If the size is too small, we insert with undefined elements.
    if (elementIndex >= this->GetSize())
    {
        this->array.insert(this->array.end(), 
            (elementIndex - this->GetSize()) + 1,
            &this->document->GetUndefinedElement());
    }
    
    this->array[elementIndex] = &element;
}

std::size_t ElementArray::GetSize(void) const
{
    return this->array.size();
}  

void ElementArray::AssignSchemasToChildElements(void)
{
    bool_t hasElement;
    
    // Clear the schema out of all child elements.
    for (Element::Iterator i = this->Begin();
         i != this->End();
         i++)
    {
        i.GetElement().SetSchemaElement(nullptr);
    }
    
    Element& itemsElement = this->schemaElement->GetElement(
        "items", &hasElement);
    
    // If "items" is defined in the schema and is an array, go through 
    // the array and assign schema elements to the matching
    // children.
    if ((hasElement) && (itemsElement.GetType() == ELEMENT_TYPE_ARRAY))
    {
        for (Element::Iterator i = itemsElement.Begin();
             i != itemsElement.End();
             i++)
        {
            uint32_t index = i.GetIndex();
            
            // Is there a child element for this index?
            Element& childElement = this->GetElement(
                index, &hasElement);
            if (hasElement)
            {
                childElement.SetSchemaElement(&(i.GetElement()));                
                childElement.AssignSchemasToChildElements();
            }
        }
    }
    
    // Special case here... either "items" or "additionalItems" can
    // be an object that is the schema for all other unspecified
    // childen.
    Element* additionalItemsElement;
    if ((hasElement) && 
        (itemsElement.GetType() == ELEMENT_TYPE_OBJECT))
    {
        additionalItemsElement = &itemsElement;
    }
    else
    {
        additionalItemsElement = 
            &this->schemaElement->GetElement("additionalItems", 
                &hasElement);
    }
    
    // If "items" or "additionalItems" is defined, and it is an object,
    // then this is the schema for every child that doesn't
    // already have one.
    if ((hasElement) && 
        (additionalItemsElement->GetType() == ELEMENT_TYPE_OBJECT))
    {
        // Iterate through all child Elements.  Set the schema
        // equal to the additonalProperties schema if it is not
        // already set.
        for (Element::Iterator i = this->Begin();
             i != this->End();
             i++)
        {
            if (i.GetElement().GetSchemaElement() == nullptr)
            {
                i.GetElement().SetSchemaElement(
                    additionalItemsElement);
                i.GetElement().AssignSchemasToChildElements();
            }
        }
    }
}
    
};
