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
    
};
