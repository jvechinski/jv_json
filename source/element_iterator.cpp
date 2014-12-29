#include "element.hpp"
#include "element_array.hpp"
#include "element_object.hpp"
#include "exception.hpp"

#include <stdio.h>

namespace JVJSON_NAMESPACE_NAME
{

Element::Iterator Element::Begin(void)
{   
    return Element::Iterator(this, true);
}

Element::Iterator Element::End(void)
{   
    return Element::Iterator(this, false);   
}

Element::Iterator Element::Find(Element& elementToFind)
{   
    Iterator i;
    
    for (i = this->Begin(); i != this->End(); i++)
    {
        if (&(*i) == &elementToFind)
        {
            break;
        }
    }
    
    return i;
}

Element::Iterator::Iterator(void)
{
    this->parentElement = nullptr;
    this->objectIterator = JVJSON_OBJECT_TYPE::iterator();
    this->arrayIterator = JVJSON_ARRAY_TYPE::iterator();
}

Element::Iterator::Iterator(Element* parentElement, bool_t begin)
{
    this->parentElement = parentElement;
    
    if (this->parentElement->GetType() == ELEMENT_TYPE_OBJECT)
    {
        ElementObject* elementObject = dynamic_cast<ElementObject*>(this->parentElement);
        if (begin)
        {
            this->objectIterator = elementObject->map.begin();
        }
        else
        {
            this->objectIterator = elementObject->map.end();
        }
    }
    else if (this->parentElement->GetType() == ELEMENT_TYPE_ARRAY)
    {
        ElementArray* elementArray = dynamic_cast<ElementArray*>(this->parentElement);
        if (begin)
        {
            this->arrayIterator = elementArray->array.begin();
        }
        else
        {
            this->arrayIterator = elementArray->array.end();
        }
    }
    else
    {
        RaiseException(
            std::runtime_error("Iterating not supported for element type %s"));
    }
}

Element& Element::Iterator::GetElement(void)
{
    if (this->parentElement->GetType() == ELEMENT_TYPE_OBJECT)
    {
        return *(this->objectIterator->second); 
    }
    else if (this->parentElement->GetType() == ELEMENT_TYPE_ARRAY)
    {
        return **(this->arrayIterator);
    }
        
    return *this->parentElement;
}

Element& Element::Iterator::GetParentElement(void)
{
    return *this->parentElement;
}

std::string Element::Iterator::GetName(void)
{
    if (this->parentElement->GetType() == ELEMENT_TYPE_OBJECT)
    {
        return this->objectIterator->first;
    }    
    else if (this->parentElement->GetType() == ELEMENT_TYPE_ARRAY)
    {
        std::size_t index = this->GetIndex();
        char s[10];
        sprintf(s, "%d", index);
        return std::string(s);
    }
        
    RaiseException(
        std::runtime_error("String names not present in JSON objects of type %s"));
    
    return "";
}

uint32_t Element::Iterator::GetIndex(void)
{
    if (this->parentElement->GetType() == ELEMENT_TYPE_ARRAY)
    {
        ElementArray* elementArray = dynamic_cast<ElementArray*>(this->parentElement);
        return this->arrayIterator - elementArray->array.begin();
    }    
    
    RaiseException(
        std::runtime_error("Integer indexes not present in JSON objects of type %s"));
        
    return 0U;
}

Element::Iterator Element::Iterator::Begin(void)
{
    return this->parentElement->Begin();
}
            
Element::Iterator Element::Iterator::End(void)
{
    return this->parentElement->End();
}

bool_t Element::Iterator::operator==(const Iterator& other)
{
    if (this->parentElement->GetType() == ELEMENT_TYPE_OBJECT)
    {
        return this->objectIterator == other.objectIterator;
    }    
    else if (this->parentElement->GetType() == ELEMENT_TYPE_ARRAY)
    {
        return this->arrayIterator == other.arrayIterator;
    }
    
    return true;
}

bool_t Element::Iterator::operator!=(const Iterator& other)
{
    return !(this->operator==(other));
}

Element::Iterator Element::Iterator::operator++(int postfix)
{
    if (this->parentElement->GetType() == ELEMENT_TYPE_OBJECT)
    {
        this->objectIterator++;
    }      
    else if (this->parentElement->GetType() == ELEMENT_TYPE_ARRAY)
    {
        this->arrayIterator++;
    }
    
    return Element::Iterator(*this);
}    

Element& Element::Iterator::operator*(void)
{
    return this->GetElement();
}
    
};
