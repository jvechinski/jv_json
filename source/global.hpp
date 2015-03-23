//////////////////////////////////////////////////////////////////////
/// @file
///
/// Global "master" header file for the JV JSON parser, controls 
/// global settings.
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

#if !defined(JVJSON_GLOBAL_HPP)
#define JVJSON_GLOBAL_HPP

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

#define JVJSON_NAMESPACE_NAME jv_json

/// This is the type used internally to represent a JSON Object.
/// Can be any object with an interface that matches the std::map
/// interface.
#define JVJSON_OBJECT_TYPE std::map<std::string,Element*>

/// This is the type used internally to represent a JSON Array.
/// Can be any object with an interface that matches the std::vector
/// interface.
#define JVJSON_ARRAY_TYPE std::vector<Element*>

/// This macro is used to determine the alignment of native types.
/// Prior to C++11, each compiler (usually) had their own syntax for
/// this.
#if __cplusplus > 199711L
#define JVJSON_NATIVE_TYPE_ALIGNMENT alignof
#else
#define JVJSON_NATIVE_TYPE_ALIGNMENT __alignof__
#endif

#endif
