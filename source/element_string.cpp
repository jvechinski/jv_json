#include "element_string.hpp"
#include "document.hpp"
#include "exception.hpp"
#include "string_conversion.hpp"

#include <cassert>

namespace JVJSON_NAMESPACE_NAME
{
    
ElementString::ElementString(const std::string& stringValue)
{
    this->hasInternalValue = true;
    
    this->value.internalValue = new std::string(stringValue);
}

ElementString::~ElementString(void)
{
    if ((this->hasInternalValue) && (this->value.internalValue))
    {
        delete this->value.internalValue;
    } 
}
    
ElementType ElementString::GetType(void) const
{
    return ELEMENT_TYPE_STRING;
}

NativeType ElementString::GetNativeType(void) const
{
    return NATIVE_TYPE_CHARACTER_ARRAY;
}

bool_t ElementString::IsValue(void) const
{
    return true;
}
  
std::string ElementString::GetValueAsString(bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = true;
    }
            
    return this->GetLocalValue();
}



bool_t ElementString::ValidateAgainstSubschema(Element& schemaElement)
{
    // Call the base class validate against schema function.
    // This will check all the common schema items, such as
    // type.
    bool_t returnValue = Element::ValidateAgainstSubschema(
        schemaElement);
    
    // Check the string length against min and max length values, if 
    // present.
    if (returnValue)
    {
        returnValue = this->ValidateLengthAgainstSubschema(
            schemaElement);
    }
    
    /// @todo "pattern" Check against a regular expression.
    
    /// @future "format" Consider supporting comparing against 
    /// format specifiers.  This part of the spec is optional.
    
    return returnValue;
}

bool_t ElementString::ValidateLengthAgainstSubschema(Element& schemaElement)
{
    bool_t hasMinLength;
    bool_t hasMaxLength;
    bool_t returnValue = true;
    
    // Check the string length against min and max length values, if 
    // present.
    Element& minLengthElement = schemaElement.GetElement(
        "minLength", &hasMinLength);
    Element& maxLengthElement = schemaElement.GetElement(
        "maxLength", &hasMaxLength);        
    if ((hasMinLength) || (hasMaxLength))
    {
        std::string stringValue = this->GetValueAsString();
        
        uint32_t stringLength = stringValue.length();
        
        if (hasMinLength)
        {
            assert(minLengthElement.IsNumber());
        }
        
        if ((hasMinLength) && 
            (stringLength < minLengthElement.GetValueAsUint32(true)))
        {
            returnValue = false;
        }

        if (hasMaxLength)
        {
            assert(maxLengthElement.IsNumber());
        }
                
        if ((hasMaxLength) && 
            (stringLength > maxLengthElement.GetValueAsUint32(true)))
        {
            returnValue = false;
        }
    }
    
    /// @todo "pattern" Check against a regular expression.
    
    return returnValue;
}
    
std::string ElementString::GetLocalValue(void)
{
    std::string returnValue("");
    
    if ((this->hasInternalValue) && (this->value.internalValue))
    {
        returnValue = *(this->value.internalValue);
    }
    
    return returnValue; 
}
   
};
