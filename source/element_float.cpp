#include "element_float.hpp"
#include "document.hpp"
#include "exception.hpp"
#include "string_conversion.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
ElementFloat::ElementFloat(floatmax_t value, NativeType type)
{
    this->hasInternalValue = true;

    if (type == NATIVE_TYPE_NONE)
    {
        this->nativeType = NATIVE_TYPE_FLOAT64;
    }
    else
    {
        switch (type)
        {
            case NATIVE_TYPE_FLOAT32:
            case NATIVE_TYPE_FLOAT64:
                this->nativeType = type;
                break;
            default:
                // Exception
                break;
        }
    }    
    
    this->value.internalValue = value;
}
    
ElementType ElementFloat::GetType(void) const
{
    return ELEMENT_TYPE_FLOAT;
}
  
float32_t ElementFloat::GetValueAsFloat32(bool_t allowConversion, bool_t* valid)
{    
    return (float32_t)this->GetLocalValue();    
}

float64_t ElementFloat::GetValueAsFloat64(bool_t allowConversion, bool_t* valid)
{    
    return (float64_t)this->GetLocalValue();    
}
    
std::string ElementFloat::GetValueAsString(bool_t allowConversion, bool_t* valid)
{
    if (allowConversion)
    {
        if (valid)
        {
            *valid = true;
        }
        
        return ToString(this->GetLocalValue());
    }
    
    return Element::GetValueAsString(allowConversion, valid);    
}
    
floatmax_t ElementFloat::GetLocalValue(void)
{
    floatmax_t returnValue = 0.0;
    
    if (this->hasInternalValue)
    {
        returnValue = this->value.internalValue;
    }
    
    return returnValue; 
}
    
};
