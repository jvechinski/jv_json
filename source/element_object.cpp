#include "element_object.hpp"
#include "document.hpp"
#include "exception.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
ElementType ElementObject::GetType(void) const
{
    return ELEMENT_TYPE_OBJECT;
}
    
Element& ElementObject::GetElement(const std::string& elementName, bool_t& exists)
{
    // Call parent class GetElement.
    //Element& e = Element::GetElement(this, elementName, exists);
    
    //if (!exists)
    //{
    //    return e;
    //}
    
    JVJSON_OBJECT_TYPE::iterator search = this->map.find(elementName); 
    if (search != this->map.end())
    {
        exists = true;
        return *search->second;
    }

    exists = false;        
    return this->document->GetUndefinedElement();
}

void ElementObject::AddElement(const std::string& elementName, Element& element)
{
    this->map[elementName] = &element;
}
    
};
