#include "element_object.hpp"
#include "document.hpp"
#include "exception.hpp"

#include <cassert>

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
    // Call the parent class AddElement() function, which performs
    // common add behavior.
    Element::AddElement(element);
    
    this->map[elementName] = &element;
}

std::size_t ElementObject::GetSize(void) const
{
    return this->map.size();
}

void ElementObject::AssignSchemasToChildElements(void)
{
    bool_t hasElement;
    
    // Clear the schema out of all child elements.
    for (Element::Iterator i = this->Begin();
         i != this->End();
         i++)
    {
        i.GetElement().SetSchemaElement(nullptr);
    }
    
    Element& propertiesElement = this->schemaElement->GetElement(
        "properties", &hasElement);
    
    // If "properties" is defined in the schema, go through the
    // object and assign schema elements to the matching
    // children.
    if (hasElement)
    {
        assert(propertiesElement.GetType() == ELEMENT_TYPE_OBJECT);
        
        for (Element::Iterator i = propertiesElement.Begin();
             i != propertiesElement.End();
             i++)
        {
            std::string propertyName = i.GetName();
            
            // Is there a child element matching the property
            // name?
            Element& childElement = this->GetElement(
                propertyName, &hasElement);
            if (hasElement)
            {
                childElement.SetSchemaElement(&(i.GetElement()));                
                childElement.AssignSchemasToChildElements();
            }
        }
    }
    
    Element& additionalPropertiesElement = 
        this->schemaElement->GetElement("additionalProperties", 
            &hasElement);
    
    // If "additionalProperties" is defined, and it is an object,
    // then this is the schema for every child that doesn't
    // already have one.
    if ((hasElement) && 
        (additionalPropertiesElement.GetType() == ELEMENT_TYPE_OBJECT))
    {
        // Iterate through all child Elements.  Set the schema
        // equal to the additonalProperties schema if it is not
        // already set.
        for (Element::Iterator i = this->Begin();
             i != this->End();
             i++)
        {
            if (i.GetElement().GetSchemaElement() == nullptr)
            {
                i.GetElement().SetSchemaElement(
                    &additionalPropertiesElement);
                i.GetElement().AssignSchemasToChildElements();
            }
        }
    }
}
    
};
