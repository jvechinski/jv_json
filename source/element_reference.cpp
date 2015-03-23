//////////////////////////////////////////////////////////////////////
/// @file
///
/// Header file for JSON Element Reference class.  Represents a JSON
/// Reference.  
///
/// The JSON reference syntax is described / proposed by the 
/// following draft:
/// https://tools.ietf.org/html/draft-pbryan-zyp-json-ref-03
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

#include "element_reference.hpp"
#include "document.hpp"

namespace JVJSON_NAMESPACE_NAME
{

ElementReference::ElementReference(const std::string& referencePath, Document* document)
{
    this->referencedElement = nullptr;
    this->document = document;
    this->SetReferencePath(referencePath);
    this->ResolveReferencedElement();
}    

ElementType ElementReference::GetType(void) const
{
    return this->GetReferencedElement().GetType();
}

NativeType ElementReference::GetNativeType(void) const
{
    return this->GetReferencedElement().GetNativeType();
}

std::size_t ElementReference::GetSize(void) const
{
    return this->GetReferencedElement().GetSize();
}  

bool_t ElementReference::IsNull(void) const
{
    return this->GetReferencedElement().IsNull();
}

bool_t ElementReference::IsValue(void) const
{
    return this->GetReferencedElement().IsValue();
}

bool_t ElementReference::IsNumber(void) const
{
    return this->GetReferencedElement().IsNumber();
}

bool_t ElementReference::IsContainer(void) const
{
    return this->GetReferencedElement().IsContainer();
}

bool_t ElementReference::IsReference(void) const
{
    return true;
}

std::string ElementReference::GetReferencePath(void)
{
    return this->referencePath;
}

void ElementReference::SetReferencePath(const std::string& referencePath)
{
    this->referencePath = referencePath;
}

Element& ElementReference::GetReferencedElement(void) const
{
    return *this->referencedElement;
}

void ElementReference::ResolveReferencedElement(void)
{
    bool_t referencedElementExists = false;
    
    Element& re = this->GetElement(this->GetReferencePath(),
        &referencedElementExists);
        
    if (referencedElementExists)
    {
        this->referencedElement = &(re);
    }
    else if (this->document)
    {
        this->referencedElement = &(this->document->GetUndefinedElement());
    }
}

};
