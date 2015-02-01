//////////////////////////////////////////////////////////////////////
/// @file
///
/// Element type helper functions.  
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

#include "global.hpp"
#include "types.hpp"
#include "element_type.hpp"

namespace JVJSON_NAMESPACE_NAME
{

const char* ElementTypeToSchemaString(ElementType type)
{
    const char* string;
    
    switch (type)
    {
        case ELEMENT_TYPE_NULL:
            string = "null";
            break;
        case ELEMENT_TYPE_INTEGER:
            string = "integer";
            break;  
        case ELEMENT_TYPE_FLOAT:
            string = "number";
            break;        
        case ELEMENT_TYPE_STRING:
            string = "string";
            break;
        case ELEMENT_TYPE_BOOLEAN:
            string = "boolean";
            break;
        case ELEMENT_TYPE_ARRAY:
            string = "array";
            break;
        case ELEMENT_TYPE_OBJECT:
            string = "object";
            break;                        
        case ELEMENT_TYPE_REFERENCE:
        case ELEMENT_TYPE_UNDEFINED:
        default:
            string = "";
            break;            
    }
    
    return string;
}

};
