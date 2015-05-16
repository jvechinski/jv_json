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
close to meeting the requirements for this application.  
However, its license meant that it could not be used.  
Also, it was missing a few features, notably support for default values.   
So JV JSON was born.

Document Objects
----------------

Document objects represent a single JSON document or file.  The
simplest code to parse a JSON file involves creating a Document
and then calling .

    #include <jv_json.hpp>
    
    jv_json::Document* document = new jv_json::Document();
    bool_t document->

Once a Document object has parsed a file, the following methods are 
commonly called on it to manipulate the document.

* **`GetRootElement()`** - Gets the root or top level element from the 
  document.
* GetElement() - Gets any individual element from the document; 
  JSON Pointer notion is suppored.

Element Objects
---------------

Elements represent a single JSON element or item in a Document.
Elements can either be simple values, like integers or strings, or
complex container types, like arrays and 

The base Element class acts like a variant, making the behavior
of all types of Elements consistent.  

The element types currently supported:

Common operations:

* GetValue() - Gets the current value of an Element.
* SetValue() - Sets the value of an Element to the provided value.

Container type elements also support additional operations:

* HasElement() - Check if a container Element contains a 
* GetElement() - 
*

JSON Pointers
-------------

The JSON Pointer (aka address) notation can be used to refer to
Elements within a Document.  This can be useful when manipulating
a deeply nested JSON file.  

Example JSON File:

Example Code:

Output:


JSON Schemas
------------

JV JSON supports validating a JSON document /file against a JSON schema. 
More information on JSON Schemas can be found at 
[json-schema.org](http://json-schema.org/).  A more user friendly 
document describing how to use JSON schemas in the real world is.

JV JSON only supports JSON schema version 4.

To validate a file against a schema, simply provide the schema 
filename to the `Document::` method.

Also note that schema file information is saved and is used to check / 
enforce requirements on Element set value operations.  This means that 
it is impossible for a document to become invalid by user action.

Default Values
--------------

JV JSON supports the "default" keyword in JSON schema files.  This
keyword allows the schema file to provide a default value if it is
missing from the file that the schema is being used to validate.

Example:




JSON References
---------------

JV JSON supports JSON References, as defined by RFC  .  Currently only 
intradocument (that is, references to other elements within the same 
document) are supported.

Reference elements appear and behave identically as the referred 
elements.  The `IsReferenced()` method can be used to determine if an 
element is a reference.

Example:



Future
------

The following features are planned for future versions of JV JSON:

[ ] "Document Manager" class to manage access to multiple open JSON 
    documents.
[ ] JSON References between documents.
[ ] Optional set value protection, to allow values to be set 
    simultaneously from multiple threads.
[ ] Transactions, to allow atomic changes of multiple element values.
[ ] JSON writer or serializer, in order to be able to save changed
    values.
[ ] Replace underlying cJSON parser with something written in C++.
[ ] Better unit tests, especially covering all Element methods for
    all Element types, and for complex JSON document cases.
[ ] Check JSON schema for validatity by validating it against the
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
