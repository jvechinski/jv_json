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
    
};

};

#endif
