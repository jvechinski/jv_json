//////////////////////////////////////////////////////////////////////
/// @file
///
/// Header file for JSON Element Integer class.  Represents a JSON
/// integer value.  
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

#if !defined(JVJSON_ELEMENT_INTEGER_HPP)
#define JVJSON_ELEMENT_INTEGER_HPP

#include "global.hpp"
#include "types.hpp"
#include "native_type.hpp"
#include "element_number.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
/// This class represents an integer value in a JSON document.
class ElementInteger : public ElementNumber
{
public:
    ElementInteger(intmax_t value, NativeType type=NATIVE_TYPE_NONE);
    ElementInteger(uintmax_t value, NativeType type=NATIVE_TYPE_NONE);

    virtual ElementType GetType(void) const;
    
    virtual uint8_t GetValueAsUint8(const bool_t allowConversion=false, bool_t* valid=nullptr);    
    virtual uint16_t GetValueAsUint16(const bool_t allowConversion=false, bool_t* valid=nullptr);
    virtual uint32_t GetValueAsUint32(const bool_t allowConversion=false, bool_t* valid=nullptr);    
    virtual uint64_t GetValueAsUint64(const bool_t allowConversion=false, bool_t* valid=nullptr);    
    virtual std::string GetValueAsString(const bool_t allowConversion=false, bool_t* valid=nullptr);

private:
    intmax_t GetLocalValueSigned(const bool_t allowConversion=false);
    uintmax_t GetLocalValueUnsigned(const bool_t allowConversion=false);

    bool_t hasInternalValue;
    bool_t isSigned;
    NativeType nativeType;

    union
    {
        intmax_t internalValueSigned;
        uintmax_t internalValueUnsigned;
        size_t valueIndex;
    } value;
};

};

#endif
