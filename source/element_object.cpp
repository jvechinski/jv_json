#include "element_object.hpp"
#include "document.hpp"
#include "exception.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
ElementType ElementObject::GetType(void) const
{
    return ELEMENT_TYPE_OBJECT;
}

bool_t ElementObject::IsContainer(void) const
{
    return true;
}  
    
Element& ElementObject::GetElementPrivate(const std::string& elementName, bool_t* exists)
{
    // Call parent class GetElementPrivate() to handle any common
    // cases (i.e. $schema).
    Element& e = Element::GetElementPrivate(elementName, exists);
    
    if (*exists)
    {
        return e;
    }
    
    JVJSON_OBJECT_TYPE::iterator search = this->map.find(elementName); 
    if (search != this->map.end())
    {
        *exists = true;
        return *search->second;
    }
    
    // e should be set to the value provided by the parent class
    // GetElementPrivate(), i.e. undefined.
    return e;
}

void ElementObject::AddElement(const std::string& elementName, Element& element)
{
    this->map[elementName] = &element;
}

std::size_t ElementObject::GetSize(void) const
{
    return this->map.size();
}  
    
};
