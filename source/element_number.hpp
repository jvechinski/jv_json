//////////////////////////////////////////////////////////////////////
/// @file
///
/// Header file for JSON Element Number class.  Represents a JSON
/// number / numeric value (integer OR floating point).
///
/// @note This is a pure virtual class that cannot be instantiated.
///
/// Part of the JV JSON parser project, 
/// https://github.com/jvechinski/jv_json
/// Released under the MIT license.
///
/// @ingroup jv_json
///
/// Copyright (c) 2015 Jeremy S. Vechinski
///
/// Permission is hereby granted, free of charge, to any person 
/// obtaining a copy of this software and associated documentation 
/// files (the "Software"), to deal in the Software without restriction, 
/// including without limitation the rights to use, copy, modify, merge, 
/// publish, distribute, sublicense, and/or sell copies of the Software, 
/// and to permit persons to whom the Software is furnished to do so, 
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be 
/// included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
/// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
/// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS 
/// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
/// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
/// SOFTWARE.
//////////////////////////////////////////////////////////////////////

#if !defined(JVJSON_ELEMENT_NUMBER_HPP)
#define JVJSON_ELEMENT_NUMBER_HPP

#include "global.hpp"
#include "types.hpp"
#include "element.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <iostream>

namespace JVJSON_NAMESPACE_NAME
{
    
/// This class represents a numeric value (floating point OR integer) 
/// in a JSON document.
class ElementNumber : public Element
{
public:
    virtual ElementType GetType(void) const = 0;
    
    virtual bool_t IsValue(void) const;
    virtual bool_t IsNumber(void) const;
    
    template <class number_t> static bool_t ValidateValueInRange(
        Element& schemaElement, number_t currentValue);
    template <class number_t> static bool_t ValidateValueIsMultipleOf(
        Element& schemaElement, number_t currentValue);

    template <class number_t> static number_t Modulus(number_t dividend, number_t divisor);
    
    template <class number_t> static number_t GetMinimumForNativeType(void);
    
    template <class number_t> static number_t GetMaximumForNativeType(void);
};

template <class number_t> bool_t ElementNumber::ValidateValueInRange(
    Element& schemaElement, number_t currentValue)
{
    number_t minimum = ElementNumber::GetMinimumForNativeType<number_t>();
    number_t maximum = ElementNumber::GetMaximumForNativeType<number_t>();
    bool_t hasElement;
    bool_t exclusiveMinimum;
    bool_t exclusiveMaximum;
    bool_t returnValue = true;
   
    Element& minimumElement = schemaElement.GetElement(
        "minimum", &hasElement);
    if (hasElement)
    {
        assert(minimumElement.IsNumber());
        minimumElement.GetValue(minimum, true);
    }
    
    Element& exclusiveMinimumElement = schemaElement.GetElement(
        "exclusiveMinimum", &exclusiveMinimum);
    if (exclusiveMinimum)
    {
        assert(exclusiveMinimumElement.GetType() == 
            ELEMENT_TYPE_BOOLEAN);
        exclusiveMinimum = exclusiveMinimumElement.GetValueAsBool();
    }
    
    Element& maximumElement = schemaElement.GetElement(
        "maximum", &hasElement);
    if (hasElement)
    {
        assert(maximumElement.IsNumber());
        maximumElement.GetValue(maximum, true);
    }    

    Element& exclusiveMaximumElement = schemaElement.GetElement(
        "exclusiveMaximum", &exclusiveMaximum);
    if (exclusiveMaximum)
    {
        assert(exclusiveMaximumElement.GetType() == 
            ELEMENT_TYPE_BOOLEAN);
        exclusiveMaximum = exclusiveMaximumElement.GetValueAsBool();
    }
    
    if (exclusiveMinimum)
    {
        if (currentValue <= minimum)
        {
            returnValue = false;
        }
    }
    else
    {
        if (currentValue < minimum)
        {
            returnValue = false;
        }        
    }
    
    if (exclusiveMaximum)
    {
        if (currentValue >= maximum)
        {
            returnValue = false;
        }       
    }
    else
    {
        if (currentValue > maximum)
        {
            returnValue = false;
        }               
    }

    //std::cout << "Minimum " << minimum  << "\n";
    //std::cout << "Maximum " << maximum  << "\n";
    //std::cout << "Value " << currentValue  << "\n";
    //std::cout << "Result " << returnValue  << "\n";
    //printf("Maximum %f\n", maximum);
    
    return returnValue; 
}

template <class number_t> bool_t ElementNumber::ValidateValueIsMultipleOf(
    Element& schemaElement, number_t currentValue)
{
    bool_t hasMultipleOfElement;
    bool_t returnValue = true;
    
    Element& multipleOfElement = schemaElement.GetElement(
        "multipleOf", &hasMultipleOfElement);    
    
    if (hasMultipleOfElement)
    {
        assert(multipleOfElement.IsNumber());
        
        number_t multipleOf;
        multipleOfElement.GetValue(multipleOf, true);
        
        if (ElementNumber::Modulus<number_t>(currentValue, multipleOf) != ((number_t)0))
        {
            returnValue = false;
        }
    }
    
    return returnValue;
}

template <class number_t> number_t ElementNumber::Modulus(number_t dividend, number_t divisor)
{
    return dividend % divisor;
}

template <> inline floatmax_t ElementNumber::Modulus<floatmax_t>(floatmax_t dividend, floatmax_t divisor)
{
    return std::fmod(dividend, divisor);
}

template <class number_t> number_t ElementNumber::GetMinimumForNativeType(void)
{
    return std::numeric_limits<number_t>::min();
}

template <> inline floatmax_t ElementNumber::GetMinimumForNativeType<floatmax_t>(void)
{
    return std::numeric_limits<floatmax_t>::max() * -1.0;
}
    
template <class number_t> number_t ElementNumber::GetMaximumForNativeType(void)
{
    return std::numeric_limits<number_t>::max();
}

};

#endif
