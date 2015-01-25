#include "element_integer.hpp"
#include "document.hpp"
#include "exception.hpp"
#include "string_conversion.hpp"

namespace JVJSON_NAMESPACE_NAME
{

ElementInteger::ElementInteger(intmax_t value, NativeType type)
{
    this->hasInternalValue = true;
    this->isSigned = true;
    if (type == NATIVE_TYPE_NONE)
    {
        this->nativeType = NATIVE_TYPE_INT64;
    }
    else
    {
        switch (type)
        {
            case NATIVE_TYPE_INT8:
            case NATIVE_TYPE_INT16:
            case NATIVE_TYPE_INT32:
            case NATIVE_TYPE_INT64:
                this->nativeType = type;
                break;
            default:
                // Exception
                break;
        }
    }
    this->value.internalValueSigned = value;
}

ElementInteger::ElementInteger(uintmax_t value, NativeType type)
{
    this->hasInternalValue = true;
    this->isSigned = false;
    if (type == NATIVE_TYPE_NONE)
    {
        this->nativeType = NATIVE_TYPE_UINT64;
    }
    else
    {
        switch (type)
        {
            case NATIVE_TYPE_UINT8:
            case NATIVE_TYPE_UINT16:
            case NATIVE_TYPE_UINT32:
            case NATIVE_TYPE_UINT64:
                this->nativeType = type;
                break;
            default:
                // Exception
                break;
        }
    }    
    this->value.internalValueUnsigned = value;
}
    
ElementType ElementInteger::GetType(void) const
{
    return ELEMENT_TYPE_INTEGER;
}
      
uint8_t ElementInteger::GetValueAsUint8(bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = true;
    }
        
    return (uint8_t)this->GetLocalValueUnsigned(true);
}

uint16_t ElementInteger::GetValueAsUint16(bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = true;
    }

    return (uint16_t)this->GetLocalValueUnsigned(true);
}

uint32_t ElementInteger::GetValueAsUint32(bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = true;
    }
        
    return (uint32_t)this->GetLocalValueUnsigned(true);
}

uint64_t ElementInteger::GetValueAsUint64(bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = true;
    }
        
    return (uint64_t)this->GetLocalValueUnsigned(true);
}

std::string ElementInteger::GetValueAsString(bool_t allowConversion, bool_t* valid)
{
    if (allowConversion)
    {
        if (valid)
        {
            *valid = true;
        }
        
        if (this->isSigned)
        {
            return ToString(this->GetLocalValueSigned());
        }
        else
        {
            return ToString(this->GetLocalValueUnsigned());
        }
    }
    
    return Element::GetValueAsString(allowConversion, valid);    
}

intmax_t ElementInteger::GetLocalValueSigned(const bool_t allowConversion)
{
    intmax_t returnValue = 0;
    
    if (this->hasInternalValue)
    {
        if (this->isSigned)
        {
            returnValue = this->value.internalValueSigned;
        }
        else if (allowConversion)
        {
            returnValue = (intmax_t)this->value.internalValueUnsigned;
        }
        else
        {
            // Exception.
        }
    }
    
    return returnValue;
}

uintmax_t ElementInteger::GetLocalValueUnsigned(const bool_t allowConversion)
{
    uintmax_t returnValue = 0;
    
    if (this->hasInternalValue)
    {
        if (!this->isSigned)
        {
            returnValue = this->value.internalValueUnsigned;
        }
        else if (allowConversion)
        {
            returnValue = (uintmax_t)this->value.internalValueSigned;
        }
        else
        {
            // Exception.
        }
    }
    
    return returnValue;
}
    
};
