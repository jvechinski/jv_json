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

#if !defined(JVJSON_DOCUMENT_HPP)
#define JVJSON_DOCUMENT_HPP

#include "global.hpp"
#include "types.hpp"
#include "element.hpp"

namespace JVJSON_NAMESPACE_NAME
{

/// The Document class represents a single JSON document, which is
/// a hierarchy of JSON Elements.  
class Document
{

public:
    char* GetFilename(void);
    void SetFilename(const char* filename);

    char* GetSchemaFilename(void);
    void SetSchemaFilename(const char* filename);
    
    Element* GetRootElement(void);

    bool_t HasElement(const char* elementName);
    bool_t HasElement(uint32_t elementIndex);
    
    Element* GetElement(const char* elementName);
    Element* GetElement(uint32_t elementIndex);
    
    bool_t ReadFromFile(const char* filename=NULL, const char* schemaFilename=NULL);
    bool_t WriteToFile(const char* filename=NULL, const char* schemaFilename=NULL);
        
private:
    std::string filename;
    std::string schemaFilename;
    Element* rootElement;
    void* valueTable;
};

}

#endif
