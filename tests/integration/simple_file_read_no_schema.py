from testgen.cpp.unittest import Target, case, run

import _common

t = Target('simple_file_read_no_schema')                               

t.globalcode(_common.global_code())

_common.read_document_case(t)

case('check_document_contents',
     'Verifies that the document contains all the expected Elements')

t.exe(r'Element& root = document.GetRootElement();')

# Root element is a JSON object.
t.chk(r'root.GetType() == ELEMENT_TYPE_OBJECT')
t.chk(r'root.IsContainer() == true')

# Verify boolean values are present and have the right values.
t.chk(r'root.HasElement("type_bool_true") == true')
t.exe(r'Element& trueElement = root.GetElement("type_bool_true");')
t.chk(r'trueElement.GetType() == ELEMENT_TYPE_BOOLEAN')
t.chk(r'trueElement.GetValueAsBool() == true')
t.chk(r'trueElement.IsValue() == true')
t.exe(r'bool_t booleanValue = trueElement;')
t.chk(r'booleanValue == true')

t.chk(r'root.HasElement("type_bool_false") == true')
t.chk(r'root.GetElement("type_bool_false").GetType() == ELEMENT_TYPE_BOOLEAN')
#t.chk(r'root.GetElement("type_bool_false").GetValueAsBool() == false')
t.chk(r'root["type_bool_false"].GetType() == ELEMENT_TYPE_BOOLEAN')

t.chk(r'root.HasElement("type_null") == true')
t.chk(r'root.GetElement("type_null").GetType() == ELEMENT_TYPE_NULL')
t.chk(r'root.GetElement("type_null").IsNull() == true')

run()
