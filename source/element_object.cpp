#include "element.hpp"
#include "exception.hpp"

namespace JVJSON_NAMESPACE_NAME
{
    
Element& ElementObject::GetElement(const std::string& elementName, bool_t& exists)
{
    Element& e;
    
    // Call parent class GetElement.
    e = Element::GetElement(this, elementName, exists);
    
    if (!exists)
    {
        return e;
    }
    
    std::iterator search = this->map.find(); 
    if (search ==
    
    exists = false;
    return nullptr;
}

virtual void AddElement(const std::string& elementName, Element& element)
{
    this->map[elementName] = element;
}
    
};
