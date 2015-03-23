#include "element_object.hpp"
#include "document.hpp"
#include "exception.hpp"

#include <cassert>
#include <set>

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

void ElementObject::ReplaceElement(Element& elementToReplace, Element& element)
{
    std::string elementName("$$$");
    
    // Get the name of the element being replaced.  We are checking
    // to see if pointers match... this may not be the best idea?
    for (JVJSON_OBJECT_TYPE::iterator i = this->map.begin(); 
         i != this->map.end(); 
         i++)
    {
        if (i->second == &elementToReplace)
        {
            elementName = i->first;
            break;
        }
    }
    
    if (elementName != "$$$")
    {
        // Call the parent class ReplaceElement() function, which performs
        // common replace behavior.
        Element::ReplaceElement(elementToReplace, element);    
        
        this->map[elementName] = &element;
    }
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
    
    // If no schema element has been assigned to this element,
    // there is nothing to do.
    if (this->GetSchemaElement() == nullptr)
    {
        return;
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
            }
            // If there is no child element, but a default value has 
            // been specified in the schema element, we add a new child 
            // using the default element.            
            else if (i.GetElement().HasElement("default"))
            {
                /// @todo Should use copy constructor / copy function
                /// to make a deep copy of the default element.
                Element& newChildElement = 
                    i.GetElement().GetElement("default");
                this->AddElement(propertyName, newChildElement);
                newChildElement.SetSchemaElement(&(i.GetElement())); 
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
            }
        }
    }
    
    // Assign schema elements in all child elements.
    for (Element::Iterator i = this->Begin();
         i != this->End();
         i++)
    {
        i.GetElement().AssignSchemasToChildElements();
    }        
}

bool_t ElementObject::ValidateAgainstSubschema(Element& schemaElement)
{
    // Call the base class validate against schema function.
    // This will check all the common schema items, such as
    // type.
    bool_t returnValue = Element::ValidateAgainstSubschema(
        schemaElement);

    // Validate that all required properties exist in the object if this
    // is specified.
    if (returnValue)
    {
        returnValue = this->ValidateRequiredProperties(schemaElement);
    }
        
    // Validate that no additional properties exist in the object if this
    // is specified.
    if (returnValue)
    {
        returnValue = this->ValidateAdditionalProperties(schemaElement);
    }

    // Validate the object size.
    if (returnValue)
    {
        returnValue = this->ValidateSizeAgainstSubschema(schemaElement);
    }   
    
    // Validate any dependent properties.
    if (returnValue)
    {
        returnValue = this->ValidatePropertyDependencies(schemaElement);
    }    
    
    return returnValue;
}

bool_t ElementObject::ValidateRequiredProperties(Element& schemaElement)
{
    bool_t hasRequiredProperties;
    bool_t returnValue = true;
    
    Element& requiredPropertiesElement = schemaElement.GetElement(
        "required", &hasRequiredProperties); 
        
    if (hasRequiredProperties)
    {
        assert(requiredPropertiesElement.GetType() == ELEMENT_TYPE_ARRAY);
        
        // Make sure each of the required properties is actually
        // in the object.
        bool_t missingRequiredProperty = false;
        for (Element::Iterator i = requiredPropertiesElement.Begin();
             ((i != requiredPropertiesElement.End()) && (!missingRequiredProperty));
             i++)
        {
            if (!this->HasElement((*i).GetValueAsString()))
            {
                missingRequiredProperty = true;
            }
        }        
        
        if (missingRequiredProperty)
        {
            returnValue = false;
        }
    }
    
    return returnValue;
}

bool_t ElementObject::ValidateAdditionalProperties(Element& schemaElement)
{
    bool_t hasProperties;
    bool_t hasAdditionalProperties;
    bool_t returnValue = true;
    
    Element& additionalPropertiesElement = schemaElement.GetElement(
        "additionalProperties", &hasAdditionalProperties); 
        
    if ((hasAdditionalProperties) && 
        (additionalPropertiesElement.GetType() == ELEMENT_TYPE_BOOLEAN) &&
        (additionalPropertiesElement.GetValueAsBool() == false))
    {
        // Create a set with all the properties present in the
        // object.
        std::set<std::string> unmatchedProperties;
        for (Element::Iterator i = this->Begin();
             i != this->End();
             i++)
        {
            unmatchedProperties.insert(i.GetName());
        }
        
        Element& propertiesElement = schemaElement.GetElement(
            "properties", &hasProperties);            
            
        // If additionalProperties is false, all properties must be
        // in either the properties or patternProperties objects.
        if (hasProperties)
        {
            assert(propertiesElement.GetType() == ELEMENT_TYPE_OBJECT);
            
            // Remove the element from the unmatched properties
            // list. 
            for (Element::Iterator i = propertiesElement.Begin();
                 i != propertiesElement.End();
                 i++)
            {
                unmatchedProperties.erase(i.GetName());
            }
        }
        
        // If there are any unmatched properties, the return value
        // is false.
        if (!unmatchedProperties.empty())
        {
            returnValue = false;
        }
    }
    
    return returnValue;
}

bool_t ElementObject::ValidateSizeAgainstSubschema(Element& schemaElement)
{
    bool_t hasMinProperties;
    bool_t hasMaxProperties;
    bool_t returnValue = true;
    
    // Check the object size against min and max items values, if 
    // present.
    Element& minPropertiesElement = schemaElement.GetElement(
        "minProperties", &hasMinProperties);
    Element& maxPropertiesElement = schemaElement.GetElement(
        "maxProperties", &hasMaxProperties);        
    if ((hasMinProperties) || (hasMaxProperties))
    {
        std::size_t objectSize = this->GetSize();
                
        if ((hasMinProperties) && 
            (minPropertiesElement.IsNumber()) &&
            (objectSize < minPropertiesElement.GetValueAsUint32(true)))
        {
            returnValue = false;
        }
                
        if ((hasMaxProperties) && 
            (maxPropertiesElement.IsNumber()) &&
            (objectSize > maxPropertiesElement.GetValueAsUint32(true)))
        {
            returnValue = false;
        }
    }
    
    return returnValue;
}

bool_t ElementObject::ValidatePropertyDependencies(Element& schemaElement)
{
    bool_t hasPropertyDependencies;
    bool_t returnValue = true;
    
    Element& dependenciesElement = schemaElement.GetElement(
        "dependencies", &hasPropertyDependencies); 
        
    if (hasPropertyDependencies)
    {
        assert(dependenciesElement.GetType() == ELEMENT_TYPE_OBJECT);
        
        // For each dependencies element, see if we've got an array
        // of other property dependencies.
        // Note that this can also be an object which contains extra
        // schema items to be checked.  This is handled differently.
        for (Element::Iterator i = dependenciesElement.Begin();
             (i != dependenciesElement.End()) && (returnValue);
             i++)
        {
            // There is only more to do if we have the dependent
            // property, and the element is an array.
            if ((this->HasElement(i.GetName())) &&
                ((*i).GetType() == ELEMENT_TYPE_ARRAY))
            {
                // For each item in the array, make sure we have 
                // the property in question.
                for (Element::Iterator j = (*i).Begin();
                     (j != (*i).End()) && (returnValue);
                     j++)                
                {
                    if (!this->HasElement((*j).GetValueAsString()))
                    {
                        returnValue = false;
                    }
                }
            }
        }        
    }
    
    return returnValue;
}
    
};
