JV JSON
=======

Introduction
------------

JV JSON is a C++ JSON file parser.  It is designed to be 
lightweight and easy to use, and would be particularly well suited
for embedded software applications.  Feature highlights include:

* JSON Schema (version 4) Support
* Default Values From JSON Schema Files
* JSON Reference Support
* Element Referencing Via JSON Pointers
* Schema Rules Enforced On Set Value Operations
* Element "Variant" Class For All JSON Types

Motivation
----------

Why create another JSON parser?  The requirements for an embedded
software application called for a C or C++ based JSON parser that 
supported JSON schemas, obtaining default values from schemas, and 
JSON references.  It would also be helpful for this application if the 
parser provided a C++ variant class for dealing with the different 
types of data that can appear in a JSON file, and was mainly 
self-contained (i.e. did not require a lot of additional support
libraries to bloat the code).

[libvariant from gallen](https://bitbucket.org/gallen/libvariant) comes 
close to meeting the requirements for this application.  However, its 
GPL license meant that it could not be used.  Also, it was missing a 
few features, notably support for default values.  So JV JSON was born.

Document Objects
----------------

Document objects represent a single JSON document or file.  The
simplest code to parse a JSON file involves creating a Document
and then calling `ReadFromFile()`.

    #include <jv_json.hpp>
    
    jv_json::Document* document = new jv_json::Document();
    bool_t result = document->ReadFromFile("sample.json");

Once a Document object has parsed a file, the following methods are 
commonly called on it to manipulate the document.

* **`GetRootElement()`** - Gets the root or top level element from the 
  document.
* **`GetElement(element)`** - Gets any individual element from the 
  document; JSON Pointer notion is suppored.

Element Objects
---------------

Elements represent a single JSON element or item in a Document.
Elements can either be simple values, like integers or strings, or
complex container types, like arrays and objects (dictionaries).

The base Element class acts like a variant, making the behavior
of all types of Elements consistent.  

The element types currently supported:

* Null
* Boolean
* Integer
* Float
* String 
* Array
* Object

Frequently used operations:

* **`GetType()`** - Gets the type of an Element.
* **`IsContainer()`** - Returns a boolean indicating whether this is a 
  container type or a simple type.
* **`GetValue(valueReference)`** - Gets the current value of an 
  Element.  A reference to a variable is passed in, and the variable 
  value is set equal to the Element value.
* **`GetValueAs...()`** - Alternative way to get the value of an 
  Element.  Returns the value of the Element as the data type specified
  (i.e. GetValueAsFloat64() would return the value as a 64-bit floating
   point number).
* **`SetValue(value)`** - Sets the value of an Element to the provided 
  value.

Container type elements also support additional operations:

* **`HasElement(elementNameOrIndex)`** - Check if a container Element 
  contains a child element specified.
* **`GetElement(element)`** - Returns a reference to the child element
  specified.
* **`operator[]`** - The [] operator works the same as GetElement() on
  container types.

JSON Pointers
-------------

The JSON Pointer (aka address) notation can be used to refer to
Elements within a Document.  JSON Pointer notation is specified in
[RFC 6901](http://www.rfc-archive.org/getrfc.php?rfc=6901). This 
syntax can be useful when manipulating a deeply nested JSON file.  

Example JSON File:

    {
        "type_array": [
            1, 
            2.0, 
            "hello", 
            {
                "deep_bool_true": true, 
                "deep_string": "jv_json"
            }, 
            true, 
            false
        ], 
        "type_bool_false": false, 
        "type_bool_true": true, 
        "type_float": -3.14, 
        "type_float_exponent": 4e-24, 
        "type_integer": 55, 
        "type_null": null, 
        "type_string": "world"
    }

Example Code:

    #include <iostream>
    #include <jv_json.hpp>
    
    jv_json::Document* document = new jv_json::Document();
    bool_t result = document->ReadFromFile("sample.json");
    Element& rootElement = document->GetRootElement();
    
    // Use JSON pointers to access values of deeply nested 
    // elements.
    std::cout << "deep_bool_true value: " << 
        document->GetElement("#/type_array/3/deep_bool_true").GetValueAsBool() << std::endl;
    std::cout << "deep_string value: " << 
        rootElement->GetElement("#/type_array/3/deep_string").GetValueAsString() << std::endl;
        
Output:

    deep_bool_true value: true
    deep_string value: jv_json

JSON Schemas
------------

JV JSON supports validating a JSON document or file against a JSON schema. 
More information on JSON Schemas can be found at 
[json-schema.org](http://json-schema.org/).  A more user friendly 
document describing how to use JSON schemas in the real world is
[Understanding JSON Schema](http://spacetelescope.github.io/understanding-json-schema/).

JV JSON only supports JSON schema version 4.

To validate a file against a schema, simply provide the schema 
filename to the `Document::ReadFromFile` method.  If the document 
validates against the schema, `ReadFromFile()` will return true.

Also note that schema file information is saved and is used to check / 
enforce requirements on Element set value operations.  This means that 
it is impossible for a document to become invalid by normal user action.

Default Values
--------------

JV JSON supports the optional "default" keyword in JSON schema files.  This 
keyword allows the schema file to provide a default value if it is
missing from the file that the schema is being used to validate.

Example JSON File:

    {
        "type_bool_true": true, 
        "type_string": "world"
    }

Example JSON Schema:

    {
        "type": "object",
        "properties": {
            "type_bool_true": {
                "type": "boolean"
            }, 
            "type_string": {            
                "type": "string"
            }
            "type_integer": {
                "type": "integer",
                "default": 55
            }
        }    
    }

Example Code:

    #include <iostream>
    #include <jv_json.hpp>
    
    jv_json::Document* document = new jv_json::Document();
    bool_t result = document->ReadFromFile("sample.json");
    
    Element& defaultIntegerElement = document->GetElement("#/type_integer");
    
    std::cout << "Default integer element, value " << 
        array1Element.GetValueAsInt32() << std::endl;

Output:
        
    Default integer element, value 55

JSON References
---------------

JV JSON supports JSON References, as defined by [this draft RFC](https://tools.ietf.org/html/draft-pbryan-zyp-json-ref-02).  
Currently only intradocument (that is, references to other elements 
within the same document) are supported.

Reference elements appear and behave identically as the referred 
elements.  The `IsReferenced()` method of the Element class can be 
used to determine if an element is a reference.

Example JSON File:

    {
        "type_array": [
            1, 
            2.0, 
            "hello", 
            {
                "deep_bool_true": true, 
                "deep_string": "jv_json"
            }, 
            true, 
            false
        ], 
        "type_reference": { '$ref': '#/type_array/1' }
    }

Example Code:

    #include <iostream>
    #include <jv_json.hpp>
    
    jv_json::Document* document = new jv_json::Document();
    bool_t result = document->ReadFromFile("sample.json");
    
    Element& array1Element = document->GetElement("#/type_array/1");
    Element& referenceElement = document->GetElement("#/type_reference");
    
    std::cout << "type_array[1], value " << array1Element.GetValueAsFloat32() <<
        ", is reference " << array1Element.IsReference() << std::endl;

    std::cout << "type_reference, value " << referenceElement.GetValueAsFloat32() <<
        ", is reference " << referenceElement.IsReference() << std::endl;
        
Output:

    type_array[1], value 2.000000, is reference false
    type_reference, value 2.000000, is reference true

Future
------

The following features are planned for future versions of JV JSON:

- [ ] "Document Manager" class to manage access to multiple open JSON 
      documents.
- [ ] JSON References between documents.
- [ ] Optional set value protection, to allow values to be set 
      simultaneously from multiple threads.
- [ ] Transactions, to allow atomic changes of multiple element values.
- [ ] JSON writer or serializer, in order to be able to save changed
      values.
- [ ] Replace underlying cJSON parser with something written in C++.
- [ ] Better unit tests, especially covering all Element methods for
      all Element types, and for complex JSON document cases.
- [ ] Check JSON schema for validatity by validating it against the
      meta schema.

License
-------

JV JSON is released under the MIT license.  The author would appreciate 
getting any bug fixes or enhancements made to the source code, but
providing this is not required.  As with any MIT licensed open source
software, feel free to use this in your commercial project or product.

*Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation 
files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:*

*The above copyright notice and this permission notice shall be 
included in all copies or substantial portions of the Software.*

*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS 
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.*
