from testgen.cpp.unittest import Target, case, run

import _common

t = Target('element_object')                               

t.globalcode(_common.global_code())

_common.read_document_case(t)

case('types',
     'Verifies that the type values returned for an object are correct')

t.dec(r'Element& object = document.GetRootElement();')

# Root element is a JSON object.
t.chk(r'object.GetType() == ELEMENT_TYPE_OBJECT')

# Objects have no native type (no value storage)
t.chk(r'object.GetNativeType() == NATIVE_TYPE_NONE')

# Objects are container types
t.chk(r'object.IsContainer() == true')

case('size',
     'Verifies that the Size() function works properly')

t.dec(r'Element& object = document.GetRootElement();')

t.chk(r'object.GetSize() == 7')

case('has_functions',
     'Verifies that the HasElement() functions work properly')

t.dec(r'Element& object = document.GetRootElement();')

# Element name in object
t.chk(r'object.HasElement("type_bool_true") == true')
t.chk(r'object.HasElement(std::string("type_bool_false")) == true')
# Element name not in object
t.chk(r'object.HasElement("doesnt_exist") == false')
t.chk(r'object.HasElement(std::string("bad_name")) == false')
# Element index cannot be used
t.chk(r'object.HasElement(1) == false')

case('get_functions',
     'Verifies that the GetElement() functions work properly')

t.dec('bool_t exists=false;')
t.dec('bool_t exception=false;')
t.dec(r'Element& object = document.GetRootElement();')

# Element name in object
t.chk(r'object.GetElement("type_bool_true").GetValueAsBool() == true')
t.chk(r'object.GetElement(std::string("type_bool_false"), &exists).GetValueAsBool() == false')
t.chk(r'exists==true')
# Element name not in object
t.exe(r'try { object.GetElement("doesnt_exist"); } catch (const std::runtime_error& e) { exception = true; }')
t.chk(r'exception==true')
t.chk(r'&object.GetElement(std::string("bad_name"), &exists) == &document.GetUndefinedElement()')
t.chk(r'exists==false')
# Element index cannot be used
t.exe(r'exists==true;')
t.chk(r'&object.GetElement(1, &exists) == &document.GetUndefinedElement()')
t.chk(r'exists==false')

case('add_function',
     'Verifies that the AddElement() function works properly')

t.dec(r'Element& object = document.GetRootElement();')
t.dec(r'Element newElement = Element();')
t.dec(r'std::size_t originalSize = object.GetSize();')

t.exe(r'object.AddElement("new_element", newElement);')

t.chk(r'object.GetSize()==(originalSize+1)')
t.chk(r'object.HasElement("new_element")==true')

run()
