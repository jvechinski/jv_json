//////////////////////////////////////////////////////////////////////
/// @file
///
/// Header file for JSON Element Float class.  Represents a JSON
/// floating point value.  
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

#if !defined(JVJSON_ELEMENT_FLOAT_HPP)
#define JVJSON_ELEMENT_FLOAT_HPP

#include "global.hpp"
#include "types.hpp"
#include "element_number.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
/// This class represents a floating point value in a JSON 
/// document.
class ElementFloat : public ElementNumber
{
public:
    ElementFloat(floatmax_t value, NativeType type=NATIVE_TYPE_NONE);
    
    virtual ElementType GetType(void) const;

    virtual float32_t GetValueAsFloat32(bool_t allowConversion=false, bool_t* valid=nullptr);
    virtual float64_t GetValueAsFloat64(bool_t allowConversion=false, bool_t* valid=nullptr);            
    virtual std::string GetValueAsString(const bool_t allowConversion=false, bool_t* valid=nullptr);
    
private:
    floatmax_t GetLocalValue(void);

    bool_t hasInternalValue;
    NativeType nativeType;

    union
    {
        floatmax_t internalValue;
        size_t valueIndex;
    } value;    
};

};

#endif
