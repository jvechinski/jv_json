//////////////////////////////////////////////////////////////////////
/// @file
///
/// Header file for JSON Element Array class.  Represents a JSON
/// Array (vector, list).  
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

#if !defined(JVJSON_ELEMENT_ARRAY_HPP)
#define JVJSON_ELEMENT_ARRAY_HPP

#include "global.hpp"
#include "types.hpp"
#include "element.hpp"

#include <string>

namespace JVJSON_NAMESPACE_NAME
{
    
/// This class represents an object (mapping, dictionary) in a JSON 
/// document.
class ElementArray : public Element
{

/// Allow the generic element iterator class to access private members.    
friend class Element::Iterator;    
    
public:
    virtual ElementType GetType(void) const;
    virtual bool_t IsContainer(void) const;
    virtual void AddElement(const uint32_t elementIndex, Element& element);

    virtual std::size_t GetSize(void) const;
    
    virtual void AssignSchemasToChildElements(void);
    
protected:
    virtual Element& GetElementPrivate(const std::string& elementName, bool_t* exists);
    virtual Element& GetElementPrivate(const uint32_t elementIndex, bool_t* exists);
    
    virtual bool_t ValidateAgainstSubschema(Element& schemaElement); 

private:
    bool_t ValidateAdditionalItems(Element& schemaElement);
    bool_t ValidateSizeAgainstSubschema(Element& schemaElement);
    bool_t ValidateUniqueItems(Element& schemaElement);

    JVJSON_ARRAY_TYPE array;

};

};

#endif
