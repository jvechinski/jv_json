from testgen.cpp.unittest import Target, case, run

import _common

t = Target('simple_file_read_with_schema')                               

t.globalcode(_common.global_code())

_common.read_document_case(t, read_schema=True)

case('check_document_contents',
     'Verifies that the document contains all the expected Elements')

t.exe(r'Element& root = document.GetRootElement();')

# Root element is a JSON object.
t.chk(r'root.GetType() == ELEMENT_TYPE_OBJECT')
t.chk(r'root.IsContainer() == true')

run()
