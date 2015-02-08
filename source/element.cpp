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

bool_t Element::IsReference(void) const
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

uintmax_t Element::GetValueAsUintMax(const bool_t allowConversion, bool_t* valid)
{
    return this->GetValueAsUint64(allowConversion, valid);
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

intmax_t Element::GetValueAsIntMax(const bool_t allowConversion, bool_t* valid)
{
    return this->GetValueAsInt64(allowConversion, valid);
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

floatmax_t Element::GetValueAsFloatMax(const bool_t allowConversion, bool_t* valid)
{
    return this->GetValueAsFloat64(allowConversion, valid);
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

void Element::GetValue(bool_t& valueVariable, const bool_t allowConversion)
{
    valueVariable = this->GetValueAsBool(allowConversion);
}

void Element::GetValue(uint64_t& valueVariable, const bool_t allowConversion)
{
    valueVariable = this->GetValueAsUint64(allowConversion);
}

void Element::GetValue(int64_t& valueVariable, const bool_t allowConversion)
{
    valueVariable = this->GetValueAsInt64(allowConversion);
}

void Element::GetValue(float32_t& valueVariable, const bool_t allowConversion)
{
    valueVariable = this->GetValueAsFloat32(allowConversion);
}

void Element::GetValue(float64_t& valueVariable, const bool_t allowConversion)
{
    valueVariable = this->GetValueAsFloat64(allowConversion);
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

int32_t Element::CompareElementValues(Element& otherElement, const bool_t allowConversion)
{
    int32_t returnValue = 0;
    
    if (!allowConversion)
    {
        if (this->GetType() != otherElement.GetType())
        {
            returnValue = -1;
        }
    }
    
    return returnValue;
}

bool_t Element::ElementValuesAreEqual(Element& otherElement, const bool_t allowConversion)
{
    return (this->CompareElementValues(otherElement, allowConversion) == 0);
}

bool_t Element::ElementValuesAreNotEqual(Element& otherElement, const bool_t allowConversion)
{
    return (this->CompareElementValues(otherElement, allowConversion) != 0);
}

void Element::AssignSchemasToChildElements(void)
{
    return;
}

Element* Element::GetSchemaElement(void)
{
    return this->schemaElement;
}

void Element::SetSchemaElement(Element* schemaElement)
{
    this->schemaElement = schemaElement;
}

bool_t Element::ValidateAgainstSchema(bool_t raiseException)
{
    bool_t returnValue = true;
        
    if (this->schemaElement)
    {       
        returnValue = this->ValidateAgainstSchemaInternal(
            *this->schemaElement);
    }
    
    return returnValue;
}

static uint32_t CountTrueItemsInArray(std::vector<bool_t>& array)
{
    uint32_t trueCount = 0;
    std::vector<bool_t>::iterator iterator;
    
    for (iterator = array.begin(); iterator < array.end(); iterator++)
    {
        if (*iterator)
        {
            trueCount += 1;
        }
    }
    
    return trueCount;
}

bool_t Element::ValidateAgainstSchemaInternal(Element& schemaElement)
{
    bool_t hasElement;
    
    //printf("ValidateAgainstSchemaInternal\n");
    
    bool_t returnValue = this->ValidateAgainstSubschema(schemaElement);

    // Handle any "not" subschema.
    Element& notElement = schemaElement.GetElement(
        "not", &hasElement);
    if ((hasElement) && (returnValue))
    {
        //printf("Checking not element\n");
        returnValue = !(this->ValidateAgainstSchemaInternal(notElement));
        //printf("Not return value %d\n", returnValue);
    }
    
    // Handle any compound subschema, such as anyOf, allOf, oneOf,
    // etc.
    const char_t* COMPOUND_KEYWORDS[] = {"anyOf", "allOf", "oneOf"};
    for (uint32_t i = 0; i < 3; i++)
    {
        const char_t* compoundKeyword = COMPOUND_KEYWORDS[i];
        
        Element& compoundElement = schemaElement.GetElement(
            compoundKeyword, &hasElement);
            
        if ((hasElement) && (returnValue))
        {
            //printf("Checking compound element %s\n", compoundKeyword);
            
            // Compound subschemas should be in an array.
            assert(compoundElement.GetType() == ELEMENT_TYPE_ARRAY);
            
            std::vector<bool_t> resultArray;
            
            // For each subschema in the compound, call ourselves
            // recursively to evaluate each one.  Store the results
            // in an array.
            for (Element::Iterator j = compoundElement.Begin();
                 j != compoundElement.End();
                 j++)
            {
                bool_t compoundResult = 
                    this->ValidateAgainstSchemaInternal(
                        j.GetElement());
                resultArray.push_back(compoundResult);
            }
            
            uint32_t trueCount = CountTrueItemsInArray(resultArray);
            
            // allOf... requires that all subschemas are true.
            if ((std::string(compoundKeyword) == std::string("allOf")) && 
                (trueCount < compoundElement.GetSize()))
            {
                returnValue = false;
            }
            // oneOf... requires that exactly 1 subschema is true.
            else if (
                (std::string(compoundKeyword) == std::string("oneOf")) && 
                (trueCount != 1U))
            {
                returnValue = false;
            }    
            // anyOf... requires that at least one subschema is true.
            else if (trueCount == 0)
            {
                returnValue = false;
            }
        }
    }
    
    //printf("ValidateAgainstSchemaInternal, return %d\n", returnValue);
    
    return returnValue;
}

bool_t Element::ValidateAgainstSubschema(Element& schemaElement)
{
    bool_t returnValue = true;
    
    // The schema element should be an object.  We should have 
    // caught that when validating against the meta-schema.
    assert(schemaElement.GetType() == ELEMENT_TYPE_OBJECT);    
    
    returnValue = this->ValidateTypeAgainstSchema(schemaElement);
    
    if (returnValue)
    {
        returnValue = this->ValidateValueAgainstSchemaEnum(
            schemaElement);
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
                (typeElement.GetValueAsString() == std::string("number"))
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

bool_t Element::ValidateTypeAgainstSchema(Element& schemaElement)
{
    bool_t hasTypeElement;
    bool_t returnValue = true;
    
    Element& typeElement = schemaElement.GetElement(
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

bool_t Element::ValidateValueAgainstSchemaEnum(Element& schemaElement)
{
    bool_t hasEnumElement;
    bool_t returnValue = true;
    
    Element& enumElement = schemaElement.GetElement(
        "enum", &hasEnumElement);
    
    if (hasEnumElement)
    {
        // Enum values should be in an array.
        assert(enumElement.GetType() == ELEMENT_TYPE_ARRAY);
    }
    
    return returnValue;
}

};
