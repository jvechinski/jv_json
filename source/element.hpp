//////////////////////////////////////////////////////////////////////
/// @file
///
/// Header file for JSON Element class.  
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

#if !defined(JVJSON_ELEMENT_HPP)
#define JVJSON_ELEMENT_HPP

#include <string>

#include "global.hpp"
#include "types.hpp"
#include "element_type.hpp"
#include "native_type.hpp"

namespace JVJSON_NAMESPACE_NAME
{
/// Forward reference to Document class.
class Document;
    
/// This class represents a single element in a JSON document.
/// Elements can either be complex container types (i.e. Objects
/// and Arrays) or simple values (Integers, Strings, and Booleans).
class Element
{
/// Allow the Document class to access private members.    
friend class Document;    
    
public:

    virtual ElementType GetType(void) const;
    virtual NativeType GetNativeType(void) const;

    bool_t HasElement(const std::string& elementName);
    bool_t HasElement(const uint32_t elementIndex);    
    Element& GetElement(const char* elementName, bool_t* exists=nullptr);
    Element& GetElement(const std::string& elementName, bool_t* exists=nullptr);
    Element& GetElement(const uint32_t elementIndex, bool_t* exists=nullptr);
    Element& operator[](const char* elementName); 
    Element& operator[](const std::string& elementName); 
    Element& operator[](const uint32_t elementIndex); 
  
    virtual void AddElement(const std::string& elementName, Element& element);
    virtual void AddElement(const uint32_t elementIndex, Element& element);
    
    void GetValue(bool_t& valueVariable, const bool_t allowConversion=false);
    void GetValue(uint8_t& valueVariable, const bool_t allowConversion=false);
    void GetValue(uint16_t& valueVariable, const bool_t allowConversion=false);
    void GetValue(uint32_t& valueVariable, const bool_t allowConversion=false);
    void GetValue(uint64_t& valueVariable, const bool_t allowConversion=false);    
    void GetValue(int8_t& valueVariable, const bool_t allowConversion=false);
    void GetValue(int16_t& valueVariable, const bool_t allowConversion=false);
    void GetValue(int32_t& valueVariable, const bool_t allowConversion=false);
    void GetValue(int64_t& valueVariable, const bool_t allowConversion=false);
    void GetValue(std::string& valueVariable, const bool_t allowConversion=false);
    
    virtual std::size_t GetSize(void) const;
    
    virtual bool_t GetValueAsBool(const bool_t allowConversion=false, bool_t* valid=nullptr);    
    virtual uint8_t GetValueAsUint8(const bool_t allowConversion=false, bool_t* valid=nullptr);    
    virtual uint16_t GetValueAsUint16(const bool_t allowConversion=false, bool_t* valid=nullptr);
    virtual uint32_t GetValueAsUint32(const bool_t allowConversion=false, bool_t* valid=nullptr);
    /*virtual uint64_t GetValueAsUint64(bool_t allowConversion=false, bool_t* valid=nullptr);
    virtual int8_t GetValueAsInt8(bool_t allowConversion=false, bool_t* valid=nullptr);    
    virtual int16_t GetValueAsInt16(bool_t allowConversion=false, bool_t* valid=nullptr);
    virtual int32_t GetValueAsInt32(bool_t allowConversion=false, bool_t* valid=nullptr);
    virtual int64_t GetValueAsInt64(bool_t allowConversion=false, bool_t* valid=nullptr);
    virtual float32_t GetValueAsFloat32(bool_t allowConversion=false, bool_t* valid=nullptr);
    virtual float64_t GetValueAsFloat64(bool_t allowConversion=false, bool_t* valid=nullptr);*/
    virtual std::string GetValueAsString(const bool_t allowConversion=false, bool_t* valid=nullptr);
    
    operator bool();
        
    uint32_t GetValueAsBytesLe(uint8_t* buffer, uint32_t numberOfBytes=0);
    uint32_t GetValueAsBytesBe(uint8_t* buffer, uint32_t numberOfBytes=0);
    virtual uint32_t GetValueAsBytes(uint8_t* buffer, uint32_t numberOfBytes=0);

    virtual void SetValueWithBool(bool_t valueVariable, bool_t allowConversion=false, bool_t* valid=nullptr);
    
    std::string GetElementName(void);
    std::size_t GetElementIndex(void);
    std::string GetElementAddress(bool_t documentPath=false, bool_t append=false);    

    class Iterator : public std::iterator<std::forward_iterator_tag, Element>
    {
        public:
            Iterator(void);
            Iterator(Element* parentElement, bool_t begin=false);
            Element& GetElement(void);
            std::string GetName(void);
            uint32_t GetIndex(void);
            Iterator Begin(void);
            Iterator End(void);
            bool_t operator==(const Iterator& other);
            bool_t operator!=(const Iterator& other);
            Iterator operator++(int postfix);
            Element& operator*(void);
        private:
            Element* parentElement;
            JVJSON_OBJECT_TYPE::iterator objectIterator;
            JVJSON_ARRAY_TYPE::iterator arrayIterator;
    };
    
    Iterator Begin(void);
    Iterator End(void);
    Iterator Find(Element& elementToFind);
        
protected:
    virtual Element& GetElementPrivate(const std::string& elementName, bool_t* exists);
    virtual Element& GetElementPrivate(const uint32_t elementIndex, bool_t* exists);

    void AddElement(Element& element);
    
    uint32_t valueIndex;
    
    /// Pointer to the Document object that contains the element.
    Document* document;
    
    bool_t ValidateTypeAgainstSchema(void);    
    
private:    
    /// Pointer to the parent element.  If this Element is in another
    /// Element (i.e. Object or Array), this will point to the 
    /// container Element.  
    Element* parent;
    
    /// Pointer to the Element in the schema that describes the 
    /// properties of this Element.  Note that by definition, the
    /// pointer will point to an Object Element.  Will be null if there 
    /// is no schema associated with this Element.
    Element* schemaElement;
};

};

#endif
