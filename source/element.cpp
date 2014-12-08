#include "element.hpp"
#include "exception.hpp"

#include <cstring>

namespace JVJSON_NAMESPACE_NAME
{
    
Element undefinedElement;
    
bool_t Element::HasElement(const std::string& elementName) const
{
    bool_t exists;
    
    this->GetElement(elementName, exists);
    
    return exists;
}

bool_t Element::HasElement(uint32_t elementIndex) const
{
    bool_t exists;
    
    this->GetElement(elementIndex, exists);
    
    return exists;
}
    
Element& Element::GetElement(const std::string& elementName) const
{
    Element& e = undefinedElement;
    bool_t exists;
    
    e = this->GetElement(elementName, exists);
    
    if (!exists)
    {
        RaiseException(
            std::runtime_error("Get element using name %s failed"));
    }
    
    return e;
}

Element& Element::GetElement(const uint32_t elementIndex) const
{
    Element& e = undefinedElement;
    bool_t exists;
    
    e = this->GetElement(elementIndex, exists);
    
    if (!exists)
    {
        RaiseException(
            std::runtime_error("Get element using index %s failed"));
    }
    
    return e;
}

Element& Element::GetElement(const std::string& elementName, bool_t& exists) const
{
    if ((this->schemaElement) && (elementName == std::string("schema")))
    {
        exists = true;
        return *(this->schemaElement);
    }
    
    exists = false;
    return undefinedElement;
}

Element& Element::GetElement(const uint32_t elementIndex, bool_t& exists) const
{
    exists = false;
    return undefinedElement;
}
    
uint8_t Element::GetValueAsUint8(bool_t allowConversion, bool_t* valid)
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
    
};
