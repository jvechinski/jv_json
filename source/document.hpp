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

#include <deque>
#include <string>

#include "global.hpp"
#include "types.hpp"
#include "element.hpp"
#include "native_type.hpp"

/// Forward reference to cJSON item structure... we don't want to
/// unnecessarily pull the whole cJSON mess in here.
struct cJSON;

namespace JVJSON_NAMESPACE_NAME
{
    
/// The Document class represents a single JSON document, which is
/// a hierarchy of JSON Elements.  
class Document
{

public:

    std::string GetFilename(void);
    void SetFilename(const std::string& filename);

    std::string GetSchemaFilename(void);
    void SetSchemaFilename(const std::string& filename);
    
    Element& GetRootElement(void);

    bool_t HasElement(const std::string& elementName);
    bool_t HasElement(const uint32_t elementIndex);
    
    Element& GetElement(const std::string& elementName, bool_t* exists=nullptr);
    Element& GetElement(const uint32_t elementIndex, bool_t* exists=nullptr);
    
    Element& GetUndefinedElement(void);
    
    bool_t ReadFromFile(const char* filename=nullptr, const char* schemaFilename=nullptr);
    bool_t WriteToFile(const char* filename=nullptr, const char* schemaFilename=nullptr);
    
    uint8_t* GetValueTablePointer(void);
    
    bool_t ValidateAgainstSchema(bool_t raiseException=false);

    class Iterator: public std::iterator<std::forward_iterator_tag, Element>
    {
        enum ElementIteratorState
        {
            DOCUMENT_ROOT,
            PARENT_BEGIN,
            ELEMENT,
            PARENT_END
        };
        
        public:
            Iterator(void);
            Iterator(Document* document, bool_t includeParentEndState=false, bool_t begin=false);
            Element& GetElement(void);
            std::size_t GetDepth(void);
            bool_t IsParentEndState(void);
            Iterator Begin(void);
            Iterator End(void);
            bool_t operator==(const Iterator& other);
            bool_t operator!=(const Iterator& other);
            Iterator operator++(int postfix);
            Element& operator*(void);

        private:        
            Document* document;
            bool_t includeParentEndState;
            std::deque< std::pair<ElementIteratorState,Element::Iterator> > elementIterators;
    };
    
    Iterator Begin(bool_t includeParentEndState=false);
    Iterator End(void);
            
private:
    /// This is the default integer type used if no native type is
    /// explictly specified by the schema constraints.
    static const NativeType DEFAULT_NATIVE_TYPE_INTEGER = NATIVE_TYPE_INT32;

    /// This is the default floating point type used if no native type is
    /// explictly specified by the schema constraints.
    static const NativeType DEFAULT_NATIVE_TYPE_FLOAT = NATIVE_TYPE_FLOAT64;

    Element* RecursiveParseCjsonItems(cJSON* item);
    Element* ConstructElementFromCjsonItem(cJSON* item);
    Element* InternalReadFromJsonFile(std::string filename);
    bool_t PairWithSchemaElements(void);
    void HandleJsonReferences(void);
    Element& GetElementByPath(const std::string& path, bool_t* exists=nullptr);

    std::string filename;
    std::string schemaFilename;
    Element* rootElement;    
    Document* schemaDocument;
    uint8_t* valueTable;    
};

extern Element undefinedElement;

}

#endif
