#include "element_string.hpp"
#include "document.hpp"
#include "exception.hpp"
#include "string_conversion.hpp"

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
