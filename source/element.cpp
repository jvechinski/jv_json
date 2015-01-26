#include "element.hpp"
#include "document.hpp"
#include "exception.hpp"

#include <cstring>
#include <cassert>
#include <stdio.h>
#include <string>

namespace JVJSON_NAMESPACE_NAME
{

ElementType Element::GetType(void) const
{
    return ELEMENT_TYPE_UNDEFINED;
}
    
NativeType Element::GetNativeType(void) const
{
    return NATIVE_TYPE_NONE;
}
    
bool_t Element::HasElement(const std::string& elementName)
{
    bool_t exists;
    
    this->GetElementPrivate(elementName, &exists);
    
    return exists;
}

bool_t Element::HasElement(uint32_t elementIndex)
{
    bool_t exists;
    
    this->GetElementPrivate(elementIndex, &exists);
    
    return exists;
}

Element& Element::GetElement(const char* elementName, bool_t* exists)
{
    return this->GetElement(std::string(elementName), exists);
}
    
Element& Element::GetElement(const std::string& elementName, bool_t* exists)
{
    bool_t local_exists;
        
    Element& e = this->GetElementPrivate(elementName, &local_exists);
    
    if (exists == nullptr)
    {
        if (!local_exists) 
        {
            RaiseException(
                std::runtime_error("Get element from %s using name %s failed"));
        }
    }
    else
    {
        *exists = local_exists;
    }
    
    return e;
}

Element& Element::GetElement(const uint32_t elementIndex, bool_t* exists)
{
    bool_t local_exists;
    
    Element& e = this->GetElementPrivate(elementIndex, &local_exists);
    
    if (exists == nullptr)
    {
        if (!local_exists) 
        {
            RaiseException(
                std::runtime_error("Get element from %s using index %d failed"));
        }
    }
    else
    {
        *exists = local_exists;
    }
    
    return e;
}

Element& Element::operator[](const char* elementName)
{
    bool_t unused = false;
    
    return this->GetElementPrivate(elementName, &unused);
}

Element& Element::operator[](const std::string& elementName)
{
    bool_t unused = false;
    
    return this->GetElementPrivate(elementName, &unused);
}

Element& Element::operator[](const uint32_t elementIndex)
{
    bool_t unused = false;
    
    return this->GetElementPrivate(elementIndex, &unused);    
}

Element& Element::GetElementPrivate(const std::string& elementName, bool_t* exists)
{
    if ((this->schemaElement) && (elementName == std::string("schema")))
    {
        *exists = true;
        return *(this->schemaElement);
    }

    *exists = false;
    return this->document->GetUndefinedElement();
}

Element& Element::GetElementPrivate(const uint32_t elementIndex, bool_t* exists)
{
    *exists = false;
    return this->document->GetUndefinedElement();
}

void Element::AddElement(const std::string& elementName, Element& element)
{
    RaiseException(
        std::runtime_error("Cannot add child element by name to element"));
}

void Element::AddElement(const uint32_t elementIndex, Element& element)
{
    RaiseException(
        std::runtime_error("Cannot add child element by index to element"));    
}

void Element::AddElement(Element& element)
{
    element.document = this->document;
    element.parentElement = this;
}
 
bool_t Element::IsNull(void) const
{
    return false;    
}

bool_t Element::IsValue(void) const
{
    return false;    
}

bool_t Element::IsNumber(void) const
{
    return false;    
}

bool_t Element::IsContainer(void) const
{
    return false;    
}
 
bool_t Element::GetValueAsBool(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return false;
}

Element::operator bool()
{
    return this->GetValueAsBool();
}

uint8_t Element::GetValueAsUint8(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}

uint16_t Element::GetValueAsUint16(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}

uint32_t Element::GetValueAsUint32(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}

uint64_t Element::GetValueAsUint64(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0U;
}

int8_t Element::GetValueAsInt8(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0;
}

int16_t Element::GetValueAsInt16(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0;
}

int32_t Element::GetValueAsInt32(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0;
}

int64_t Element::GetValueAsInt64(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0;
}

float32_t Element::GetValueAsFloat32(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0.0;
}

float64_t Element::GetValueAsFloat64(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return 0.0;
}

std::string Element::GetValueAsString(const bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
    return std::string("");
}
    
uint32_t Element::GetValueAsBytes(uint8_t* buffer, uint32_t numberOfBytes)
{
    return 0U;
}
    
void Element::SetValueWithBool(bool_t valueVariable, bool_t allowConversion, bool_t* valid)
{
    if (valid)
    {
        *valid = false;
    }
}    

std::size_t Element::GetSize(void) const
{
    return 0;
}

void Element::GetValue(std::string& valueVariable, const bool_t allowConversion)
{
    valueVariable = this->GetValueAsString(allowConversion);
}

std::string Element::GetName(void)
{
    if (!this->parentElement)
    {
        RaiseException(
            std::runtime_error("Element has no name"));        
    }
    else
    {
        Element::Iterator i = this->parentElement->Find(*this);
        if (i == this->parentElement->End())
        {
            RaiseException(
                std::runtime_error("Cannot find element in parent"));                    
        }
        return i.GetName();
    }
    
    return std::string("");
}
    
std::size_t Element::GetIndex(void)
{
    if (!this->parentElement)
    {
        RaiseException(
            std::runtime_error("Element has no index"));        
    }
    else
    {
        Element::Iterator i = this->parentElement->Find(*this);
        if (i == this->parentElement->End())
        {
            RaiseException(
                std::runtime_error("Cannot find element in parent"));                    
        }
        return i.GetIndex();
    }
    
    return 0U;
}

std::string Element::GetAddress(bool_t documentPath, bool_t recursiveCall)
{
    if (this->parentElement)
    {
        std::string address = this->parentElement->GetAddress(documentPath, true);
        address.append("/");
        address.append(this->GetName());
        return address;
    }
    else
    {
        std::string address;
        if ((documentPath) && (this->document))
        {
            address.append(this->document->GetFilename());
        }
        address.append("#");
        if (!recursiveCall)
        {
            address.append("/");
        }
        return address;
    }
}

bool_t Element::ValidateAgainstSchema(bool_t raiseException)
{
    bool_t returnValue = true;
    
    if (this->schemaElement)
    {
        // The schema element should be an object.  We should have 
        // caught that when validating against the meta-schema.
        assert(this->schemaElement->GetType() == ELEMENT_TYPE_OBJECT);
        
        returnValue = this->ValidateTypeAgainstSchema();
    }
    
    return returnValue;
}

bool_t Element::CompareAgainstSchemaTypeElement(Element& typeElement)
{
    bool_t returnValue = true;
    
    if (typeElement.GetType() == ELEMENT_TYPE_STRING)
    {
        std::string thisElementTypeString(
            ElementTypeToSchemaString(this->GetType()));
        
        if (thisElementTypeString != typeElement.GetValueAsString())
        {
            // There is only a single special case.
            // Integer types can match both "number" and "integer" type
            // strings.
            if (
                (this->IsNumber()) &&
                (thisElementTypeString == std::string("number"))
               )
            {
                returnValue = true;
            }
            else
            {
                returnValue = false;
            }
        }
    }
    
    return returnValue;
}

bool_t Element::ValidateTypeAgainstSchema(void)
{
    bool_t hasTypeElement;
    bool_t returnValue = true;
    
    Element& typeElement = this->schemaElement->GetElement(
        "type", &hasTypeElement);
    
    if (hasTypeElement)
    {
        if (typeElement.GetType() == ELEMENT_TYPE_ARRAY)
        {
            returnValue = false;
            
            for (Element::Iterator i = typeElement.Begin();
                 (i != typeElement.End()) && (!returnValue);
                 i++)
            {
                returnValue = 
                    this->CompareAgainstSchemaTypeElement(
                        i.GetElement());                
            }
        }
        else
        {
            returnValue = 
                this->CompareAgainstSchemaTypeElement(typeElement);
        }
    }
    
    return returnValue;
}

};
