//////////////////////////////////////////////////////////////////////
/// @file
///
/// Header file for JSON Element String class.  Represents a JSON
/// string value.  
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

#if !defined(JVJSON_ELEMENT_STRING_HPP)
#define JVJSON_ELEMENT_STRING_HPP

#include "global.hpp"
#include "types.hpp"
#include "element.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
/// This class represents a floating point value in a JSON 
/// document.
class ElementString : public Element
{
public:
    ElementString(const std::string& stringValue);
    ~ElementString(void);
    
    virtual ElementType GetType(void) const;
    virtual NativeType GetNativeType(void) const;
    virtual bool_t IsValue(void) const;
         
    virtual std::string GetValueAsString(const bool_t allowConversion=false, bool_t* valid=nullptr);

protected:
    virtual bool_t ValidateAgainstSubschema(Element& schemaElement); 
    
private:
    bool_t ValidateLengthAgainstSubschema(Element& schemaElement);
    
    std::string GetLocalValue(void);

    bool_t hasInternalValue;

    union
    {
        std::string* internalValue;
        size_t valueIndex;
    } value;    
};

};

#endif
