from testgen.cpp.unittest import Target, case, run

import _common

t = Target('element_array')                               

t.globalcode(_common.global_code())

_common.read_document_case(t)

case('types',
     'Verifies that the type values returned for an array are correct')

t.dec(r'Element& array = document.GetRootElement().GetElement("type_array");')

# Element is a JSON array.
t.chk(r'array.GetType() == ELEMENT_TYPE_ARRAY')

# Arrays have no native type (no value storage)
t.chk(r'array.GetNativeType() == NATIVE_TYPE_NONE')

# Arrays are container types
t.chk(r'array.IsContainer() == true')

case('size',
     'Verifies that the Size() function works properly')

t.dec(r'Element& array = document.GetRootElement().GetElement("type_array");')

t.chk(r'array.GetSize() == 6')

case('has_functions',
     'Verifies that the HasElement() functions work properly')

t.dec(r'Element& array = document.GetRootElement().GetElement("type_array");')

# Element index in object
t.chk(r'array.HasElement(1) == true')
t.chk(r'array.HasElement("2") == true')
# Element index not in object
t.chk(r'array.HasElement(6) == false')
t.chk(r'array.HasElement("10") == false')
# Element name cannot be used
t.chk(r'array.HasElement("bad_name") == false')

case('get_functions',
     'Verifies that the GetElement() functions work properly')

t.dec('bool_t exists=false;')
t.dec('bool_t exception=false;')
t.dec(r'Element& array = document.GetRootElement().GetElement("type_array");')

# Element index in object
t.chk(r'array.GetElement(3).GetValueAsBool() == true')
t.chk(r'array.GetElement("4", &exists).GetValueAsBool() == true')
t.chk(r'exists==true')
# Element index not in object
t.exe(r'try { array.GetElement(6); } catch (const std::runtime_error& e) { exception = true; }')
t.chk(r'exception==true')
t.chk(r'&array.GetElement("1000", &exists) == &document.GetUndefinedElement()')
t.chk(r'exists==false')
# Element name cannot be used
t.exe(r'exists==true;')
t.chk(r'&array.GetElement("illegal", &exists) == &document.GetUndefinedElement()')
t.chk(r'exists==false')

case('add_function',
     'Verifies that the AddElement() function works properly')

t.dec(r'Element& array = document.GetRootElement().GetElement("type_array");')
t.dec(r'Element newElement = Element();')
t.dec(r'std::size_t originalSize = array.GetSize();')

t.exe(r'array.AddElement(originalSize, newElement);')

t.chk(r'array.GetSize()==(originalSize+1)')
t.chk(r'array.HasElement(originalSize)==true')

run()
