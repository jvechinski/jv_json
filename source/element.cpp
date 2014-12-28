#include "element.hpp"
#include "document.hpp"
#include "exception.hpp"

#include <cstring>
#include <stdio.h>

namespace JVJSON_NAMESPACE_NAME
{

ElementType Element::GetType(void) const
{
    return ELEMENT_TYPE_UNDEFINED;
}
    
NativeType Element::GetNativeType(void) const
{
    return NATIVE_TYPE_NONE;
}
    
bool_t Element::HasElement(const std::string& elementName)
{
    bool_t exists;
    
    this->GetElementPrivate(elementName, &exists);
    
    return exists;
}

bool_t Element::HasElement(uint32_t elementIndex)
{
    bool_t exists;
    
    this->GetElementPrivate(elementIndex, &exists);
    
    return exists;
}

Element& Element::GetElement(const char* elementName, bool_t* exists)
{
    return this->GetElement(std::string(elementName), exists);
}
    
Element& Element::GetElement(const std::string& elementName, bool_t* exists)
{
    bool_t local_exists;
        
    Element& e = this->GetElementPrivate(elementName, &local_exists);
    
    if (exists == nullptr)
    {
        if (!local_exists) 
        {
            RaiseException(
                std::runtime_error("Get element from %s using name %s failed"));
        }
    }
    else
    {
        *exists = local_exists;
    }
    
    return e;
}

Element& Element::GetElement(const uint32_t elementIndex, bool_t* exists)
{
    bool_t local_exists;
    
    Element& e = this->GetElementPrivate(elementIndex, &local_exists);
    
    if (exists == nullptr)
    {
        if (!local_exists) 
        {
            RaiseException(
                std::runtime_error("Get element from %s using index %d failed"));
        }
    }
    else
    {
        *exists = local_exists;
    }
    
    return e;
}

Element& Element::operator[](const char* elementName)
{
    bool_t unused = false;
    
    return this->GetElementPrivate(elementName, &unused);
}

Element& Element::operator[](const std::string& elementName)
{
    bool_t unused = false;
    
    return this->GetElementPrivate(elementName, &unused);
}

Element& Element::operator[](const uint32_t elementIndex)
{
    bool_t unused = false;
    
    return this->GetElementPrivate(elementIndex, &unused);    
}

Element& Element::GetElementPrivate(const std::string& elementName, bool_t* exists)
{
    if ((this->schemaElement) && (elementName == std::string("schema")))
    {
        *exists = true;
        return *(this->schemaElement);
    }

    *exists = false;
    return this->document->GetUndefinedElement();
}

Element& Element::GetElementPrivate(const uint32_t elementIndex, bool_t* exists)
{
    *exists = false;
    return this->document->GetUndefinedElement();
}

void Element::AddElement(const std::string& elementName, Element& element)
{
    RaiseException(
        std::runtime_error("Cannot add child element by name to element"));
}

void Element::AddElement(const uint32_t elementIndex, Element& element)
{
    RaiseException(
        std::runtime_error("Cannot add child element by index to element"));    
}

void Element::AddElement(Element& element)
{
    element.document = this->document;
    element.parent = this;
}
 
bool_t Element::GetValueAsBool(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return false;
}

Element::operator bool()
{
    return this->GetValueAsBool();
}

uint8_t Element::GetValueAsUint8(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}

uint16_t Element::GetValueAsUint16(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}

uint32_t Element::GetValueAsUint32(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}

std::string Element::GetValueAsString(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return std::string("");
}
    
uint32_t Element::GetValueAsBytes(uint8_t* buffer, uint32_t numberOfBytes)
{
    return 0U;
}
    
bool_t Element::ValidateTypeAgainstSchema(void)
{
    if (!this->schemaElement)
    {
        return false;
    }
    
    return true;
}

void Element::SetValueWithBool(bool_t valueVariable, bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
}    

std::size_t Element::GetSize(void) const
{
    return 0;
}

void Element::GetValue(std::string& valueVariable, const bool_t allowConversion)
{
    this->GetValueAsString(allowConversion);
}

};
