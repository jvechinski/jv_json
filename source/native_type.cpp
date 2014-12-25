//////////////////////////////////////////////////////////////////////
/// @file
///
/// Header file for JSON Document class.  
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

#include "global.hpp"
#include "native_type.hpp"
#include "types.hpp"

namespace JVJSON_NAMESPACE_NAME
{

const char* GetNativeTypeString(NativeType type)
{
    const char* string;
    
    switch (type)
    {
        case NATIVE_TYPE_BIT:
            string = "bit";
            break;
        case NATIVE_TYPE_UINT8:
            string = "uint8_t";
            break;
        case NATIVE_TYPE_UINT16:
            string = "uint16_t";
            break;        
        case NATIVE_TYPE_UINT32:
            string = "uint32_t";
            break;
        case NATIVE_TYPE_UINT64:
            string = "uint64_t";
            break;
        case NATIVE_TYPE_INT8:
            string = "int8_t";
            break;
        case NATIVE_TYPE_INT16:
            string = "int16_t";
            break;                        
        case NATIVE_TYPE_INT32:
            string = "int32_t";
            break; 
        case NATIVE_TYPE_INT64:
            string = "int64_t";
            break;             
        case NATIVE_TYPE_FLOAT32:
            string = "float32_t";
            break;
        case NATIVE_TYPE_FLOAT64:
            string = "float64_t";
            break;                        
        case NATIVE_TYPE_NONE:
        default:
            string = "none";
            break;            
    }
    
    return string;
}

std::size_t GetNativeTypeSize(NativeType type)
{
    std::size_t size;
    
    switch (type)
    {
        case NATIVE_TYPE_UINT8:
            size = sizeof(uint8_t);
            break;
        case NATIVE_TYPE_UINT16:
            size = sizeof(uint16_t);
            break;        
        case NATIVE_TYPE_UINT32:
            size = sizeof(uint32_t);
            break;
        case NATIVE_TYPE_UINT64:
            size = sizeof(uint64_t);
            break;
        case NATIVE_TYPE_INT8:
            size = sizeof(int8_t);
            break;
        case NATIVE_TYPE_INT16:
            size = sizeof(int16_t);
            break;                        
        case NATIVE_TYPE_INT32:
            size = sizeof(int32_t);
            break; 
        case NATIVE_TYPE_INT64:
            size = sizeof(int64_t);
            break;             
        case NATIVE_TYPE_FLOAT32:
            size = sizeof(float32_t);
            break;
        case NATIVE_TYPE_FLOAT64:
            size = sizeof(float64_t);
            break;              
        case NATIVE_TYPE_NONE:
        case NATIVE_TYPE_BIT:
        default:
            size = 0;
            break;            
    }
    
    return size;
}

std::size_t GetNativeTypeAlignment(NativeType type)
{
    std::size_t alignment;
    
    switch (type)
    {
        case NATIVE_TYPE_UINT8:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(uint8_t);
            break;
        case NATIVE_TYPE_UINT16:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(uint16_t);
            break;        
        case NATIVE_TYPE_UINT32:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(uint32_t);
            break;
        case NATIVE_TYPE_UINT64:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(uint64_t);
            break;
        case NATIVE_TYPE_INT8:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(int8_t);
            break;
        case NATIVE_TYPE_INT16:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(int16_t);
            break;                        
        case NATIVE_TYPE_INT32:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(int32_t);
            break; 
        case NATIVE_TYPE_INT64:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(int64_t);
            break;             
        case NATIVE_TYPE_FLOAT32:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(float32_t);
            break;
        case NATIVE_TYPE_FLOAT64:
            alignment = JVJSON_NATIVE_TYPE_ALIGNMENT(float64_t);
            break;                          
        case NATIVE_TYPE_NONE:
        case NATIVE_TYPE_BIT:
        default:
            alignment = 0;
            break;            
    }
    
    return alignment;
}

};
