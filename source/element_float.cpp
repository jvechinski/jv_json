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

int32_t ElementFloat::CompareElementValues(Element& otherElement, bool_t allowConversion)
{
    // Call the base class validate against schema function.
    // This will do basic comparision.
    int32_t returnValue = Element::CompareElementValues(
        otherElement, allowConversion);
        
    if (returnValue == 0)
    {
        floatmax_t thisElementValue = this->GetValueAsFloatMax();
        floatmax_t otherElementValue = otherElement.GetValueAsFloatMax(allowConversion);
        
        if (thisElementValue < otherElementValue)
        {
            returnValue = -1;
        }
        else if (thisElementValue > otherElementValue)
        {
            returnValue = 1;
        }
    }
    
    return returnValue;
}

bool_t ElementFloat::ValidateAgainstSubschema(Element& schemaElement)
{
    // Call the base class validate against schema function.
    // This will check all the common schema items, such as
    // type.
    bool_t returnValue = Element::ValidateAgainstSubschema(
        schemaElement);
        
    // Check that the current value is within the proper range.
    if (returnValue)
    {
        returnValue = ElementNumber::ValidateValueInRange<floatmax_t>
            (schemaElement, this->GetValueAsFloatMax());
    }
    
    // Check that the current value is a multiple of another value.
    if (returnValue)
    {
        returnValue = ElementNumber::ValidateValueIsMultipleOf<floatmax_t>
            (schemaElement, this->GetValueAsFloatMax());
    }    
        
    return returnValue;
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
