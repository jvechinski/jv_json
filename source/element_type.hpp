//////////////////////////////////////////////////////////////////////
/// @file
///
/// Header file for JSON element type items.
///
/// Part of the JV JSON parser project, 
/// https://github.com/jvechinski/jv_json
/// Released under the MIT license.
///
/// @ingroup jv_json
///
/// Copyright (c) 2014 Jeremy S. Vechinski
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

#if !defined(JVJSON_ELEMENT_TYPE_HPP)
#define JVJSON_ELEMENT_TYPE_HPP

#include "global.hpp"

namespace JVJSON_NAMESPACE_NAME
{

enum ElementType
{
    ELEMENT_TYPE_NULL,
    ELEMENT_TYPE_INTEGER,
    ELEMENT_TYPE_FLOAT,
    ELEMENT_TYPE_STRING,
    ELEMENT_TYPE_BOOLEAN,
    ELEMENT_TYPE_ARRAY,
    ELEMENT_TYPE_OBJECT,
    ELEMENT_TYPE_REFERENCE,
    ELEMENT_TYPE_UNDEFINED
};

const char* ElementTypeToString(ElementType type);

};

#endif
