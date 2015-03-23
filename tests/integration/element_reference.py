from testgen.cpp.unittest import Target, case, run

import _common

t = Target('element_reference')                               

t.globalcode(_common.global_code())

document = _common.get_simple_json_document()
document['type_reference'] = {'$ref': '#/type_array/0'}

_common.read_custom_document_case(t, document=document,
    name='reference_to_simple_type', 
    description='Reference to a simple (non-container) type')
t.exe('Element& e = document.GetRootElement().GetElement("type_reference");')
t.chk('e.IsReference() == true');
t.chk('e.GetType() == ELEMENT_TYPE_INTEGER');
t.chk('e.IsNumber() == true');

#document = _common.get_simple_json_document()
#document['type_reference'] = {'$ref': '#/type_array/3'}

#_common.read_custom_document_case(t, document=document,
#    name='reference_to_complex_type', 
#    description='Reference to a complex (container) type')
#t.exe('Element& e = document.GetRootElement().GetElement("type_reference");')
#t.chk('e.IsReference() == true');
#t.chk('e.GetType() == ELEMENT_TYPE_OBJECT');
#t.chk('e.IsContainer() == true');

run()
