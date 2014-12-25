#include "element_boolean.hpp"
#include "document.hpp"
#include "exception.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
ElementType ElementBoolean::GetType(void) const
{
    return ELEMENT_TYPE_BOOLEAN;
}

NativeType ElementBoolean::GetNativeType(void) const
{
    return NATIVE_TYPE_UINT8;
}
    
bool_t ElementBoolean::GetValueAsBool(bool_t allowConversion, bool_t* valid)
{
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
    
};