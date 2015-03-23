from testgen.cpp.unittest import Target, case, run

import _common

t = Target('element_reference')                               

t.globalcode(_common.global_code())

_common.read_document_case(t)

case('get_root_by_path',
     'Verifies that the root element of a document can be obtained via a path / URI')

t.dec(r'Element& e = document.GetElement("#/");')
t.dec(r'bool_t isRootElement = (&e == &(document.GetRootElement()));')

t.chk(r'isRootElement == true')

# Root element is an object
t.chk(r'e.GetType() == ELEMENT_TYPE_OBJECT')

case('get_first_by_path',
     'Verifies that a first level element of a document can be obtained via a path / URI')

t.dec(r'Element& e = document.GetElement("#/type_integer");')

# First level element is an integer
t.chk(r'e.GetType() == ELEMENT_TYPE_INTEGER')
t.chk(r'e.GetValueAsInt32() == 55')

case('get_deep_by_path',
     'Verifies that a deeply nested element of a document can be obtained via a path / URI')

t.dec(r'bool_t exists=false;')
t.dec(r'Element& e = document.GetElement("#/type_array/3/deep_bool_true", &exists);')

t.chk(r'exists == true')
t.chk(r'e.GetType() == ELEMENT_TYPE_BOOLEAN')
t.chk(r'e.GetValueAsBool() == true')

case('bad_path_1',
     'Verifies that a bad path results in returning an undefined element')

t.dec(r'bool_t exists=true;')
t.dec(r'Element& e = document.GetElement("#/type_array/3/bad_path", &exists);')
t.dec(r'bool_t isUndefinedElement = (&e == &(document.GetUndefinedElement()));')

t.chk(r'exists == false')
t.chk(r'isUndefinedElement == true')

case('path_on_element',
     'Verifies that GetPath() on an Element accepts a path / URI')

t.dec(r'bool_t exists=false;')
t.dec(r'Element& baseElement = document.GetRootElement().GetElement("type_string");')
t.dec(r'Element& e = baseElement.GetElement("#/type_array/1", &exists);')

t.chk(r'exists == true')
t.chk(r'e.GetType() == ELEMENT_TYPE_FLOAT')
t.chk(r'e.GetValueAsFloat32() == 2.0')

run()
