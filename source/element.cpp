#include "element.hpp"
#include "document.hpp"
#include "exception.hpp"

#include <cstring>

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
    
    this->GetElement(elementName, exists);
    
    return exists;
}

bool_t Element::HasElement(uint32_t elementIndex)
{
    bool_t exists;
    
    this->GetElement(elementIndex, exists);
    
    return exists;
}

Element& Element::GetElement(const char* elementName)
{
    return this->GetElement(std::string(elementName));
}
    
Element& Element::GetElement(const std::string& elementName)
{
    bool_t exists;
    
    Element& e = this->GetElement(elementName, exists);
    
    if (!exists)
    {
        RaiseException(
            std::runtime_error("Get element using name %s failed"));
    }
    
    return e;
}

Element& Element::GetElement(const uint32_t elementIndex)
{
    bool_t exists;
    
    Element& e = this->GetElement(elementIndex, exists);
    
    if (!exists)
    {
        RaiseException(
            std::runtime_error("Get element using index %s failed"));
    }
    
    return e;
}

Element& Element::GetElement(const std::string& elementName, bool_t& exists)
{
    if ((this->schemaElement) && (elementName == std::string("schema")))
    {
        exists = true;
        return *(this->schemaElement);
    }
    
    exists = false;
    return this->document->GetUndefinedElement();
}

Element& Element::GetElement(const uint32_t elementIndex, bool_t& exists)
{
    exists = false;
    return this->document->GetUndefinedElement();
}

Element& Element::operator[](const char* elementName)
{
    return this->GetElement(elementName);
}

Element& Element::operator[](const std::string& elementName)
{
    return this->GetElement(elementName);
}

//const Element& Element::operator[](const std::string& elementName) const
//{
//    return const_cast<Element&>(this->GetElement(elementName));
//}

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
 
bool_t Element::GetValueAsBool(bool_t allowConversion, bool_t* valid)
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

uint8_t Element::GetValueAsUint8(bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}

uint16_t Element::GetValueAsUint16(bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}

uint32_t Element::GetValueAsUint32(bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}
    
uint32_t Element::GetValueAsBytes(uint8_t* buffer, uint32_t numberOfBytes)
{
    return 0U;
}

uint32_t Element::GetCount(void)
{
    return 0;
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

};
