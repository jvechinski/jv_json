#include "element_boolean.hpp"
#include "document.hpp"
#include "exception.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
ElementBoolean::ElementBoolean(bool_t value)
{
    this->hasInternalValue = true;
    this->value.internalValue = value;
}
    
ElementType ElementBoolean::GetType(void) const
{
    return ELEMENT_TYPE_BOOLEAN;
}

NativeType ElementBoolean::GetNativeType(void) const
{
    return NATIVE_TYPE_UINT8;
}

bool_t ElementBoolean::IsValue(void) const
{
    return true;
}
    
bool_t ElementBoolean::GetValueAsBool(bool_t allowConversion, bool_t* valid)
{
    if (this->hasInternalValue)
    {
        return this->value.internalValue;
    }
    return true;
}
    
uint8_t ElementBoolean::GetValueAsUint8(bool_t allowConversion, bool_t* valid)
{
    if (allowConversion)
    {
        if (valid)
        {
            *valid = true;
        }
        
        if (this->GetValueAsBool())
        {
            return 1U;
        }
        else
        {
            return 0U;
        }
    }
    
    return Element::GetValueAsUint8(allowConversion, valid);    
}

uint16_t ElementBoolean::GetValueAsUint16(bool_t allowConversion, bool_t* valid)
{
    return (uint16_t)this->GetValueAsUint8();
}

uint32_t ElementBoolean::GetValueAsUint32(bool_t allowConversion, bool_t* valid)
{
    return (uint32_t)this->GetValueAsUint8();
}

std::string ElementBoolean::GetValueAsString(bool_t allowConversion, bool_t* valid)
{
    if (allowConversion)
    {
        if (valid)
        {
            *valid = true;
        }
        
        if (this->GetValueAsBool())
        {
            return std::string("true");
        }
        else
        {
            return std::string("false");
        }
    }
    
    return Element::GetValueAsString(allowConversion, valid);    
}

int32_t ElementBoolean::CompareElementValues(Element& otherElement, bool_t allowConversion)
{
    // Call the base class validate against schema function.
    // This will do basic comparision.
    int32_t returnValue = Element::CompareElementValues(
        otherElement, allowConversion);
        
    if (returnValue == 0)
    {
        bool_t thisElementValue = this->GetValueAsBool();
        bool_t otherElementValue = otherElement.GetValueAsBool(allowConversion);
        
        if (thisElementValue != otherElementValue)
        {
            if (thisElementValue == false)
            {
                returnValue = -1;
            }
            else
            {
                returnValue = 1;    
            }
        }
    }
    
    return returnValue;
}
    
};
