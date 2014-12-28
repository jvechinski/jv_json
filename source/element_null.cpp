#include "element_null.hpp"
#include "document.hpp"
#include "exception.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
ElementType ElementNull::GetType(void) const
{
    return ELEMENT_TYPE_NULL;
}

bool_t ElementNull::IsNull(void) const
{
    return true;    
}
    
bool_t ElementNull::GetValueAsBool(bool_t allowConversion, bool_t* valid)
{
    if (allowConversion)
    {
        if (valid)
        {
            *valid = true;
        }
        
        return false;
    }
    
    return Element::GetValueAsBool(allowConversion, valid);    
}
    
uint8_t ElementNull::GetValueAsUint8(bool_t allowConversion, bool_t* valid)
{
    if (allowConversion)
    {
        if (valid)
        {
            *valid = true;
        }
        
        return 0U;
    }
    
    return Element::GetValueAsUint8(allowConversion, valid);    
}

uint16_t ElementNull::GetValueAsUint16(bool_t allowConversion, bool_t* valid)
{
    return (uint16_t)this->GetValueAsUint8();
}

uint32_t ElementNull::GetValueAsUint32(bool_t allowConversion, bool_t* valid)
{
    return (uint32_t)this->GetValueAsUint8();
}

std::string ElementNull::GetValueAsString(bool_t allowConversion, bool_t* valid)
{
    if (allowConversion)
    {
        if (valid)
        {
            *valid = true;
        }
        
        return std::string("null");
    }
    
    return Element::GetValueAsString(allowConversion, valid);    
}
    
};
