//////////////////////////////////////////////////////////////////////
/// @file
///
/// Definition for string conversion functions.
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
#include "string_conversion.hpp"
#include "types.hpp"

#include <cstdio>
#include <cstring>

namespace JVJSON_NAMESPACE_NAME
{
    
const size_t MAX_STRING_SIZE = 24;

std::string ToString(int val)
{
    char tempString[MAX_STRING_SIZE];
    sprintf(tempString, "%d", val);
    return std::string(tempString);
}

std::string ToString(long val)
{
    char tempString[MAX_STRING_SIZE];
    sprintf(tempString, "%ld", val);
    return std::string(tempString);
}

std::string ToString(long long val)
{
    char tempString[MAX_STRING_SIZE];
    /// @todo Fix
    // C++98 does not support %lld?    
    sprintf(tempString, "%ld", (long)val);
    return std::string(tempString);
}

std::string ToString(unsigned val)
{
    char tempString[MAX_STRING_SIZE];
    sprintf(tempString, "%u", val);
    return std::string(tempString);
}

std::string ToString(unsigned long val)
{
    char tempString[MAX_STRING_SIZE];
    sprintf(tempString, "%lu", val);
    return std::string(tempString);
}

std::string ToString(unsigned long long val)
{
    char tempString[MAX_STRING_SIZE];
    /// @todo Fix
    // C++98 does not support %llu?
    sprintf(tempString, "%lu", (unsigned long)val);
    return std::string(tempString);
}

std::string ToString(float val)
{
    return ToString((double)val);
}

std::string ToString(double val)
{
    char tempString[MAX_STRING_SIZE];
    sprintf(tempString, "%g", val);
    if (strpbrk("eE.", tempString) == nullptr)
    {
        strcat(tempString, ".0");
    }    
    return std::string(tempString);
}

};
