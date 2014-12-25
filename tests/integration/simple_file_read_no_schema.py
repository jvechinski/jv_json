from testgen.cpp.unittest import Target, case, run

t = Target('simple_file_read_no_schema')                               

import json
f = file('simple.json', 'w')
f.write(json.dumps({'type_bool_true': True,
                    'type_bool_false': False,
                    'type_integer': 5, 
                    'type_float': 7.0}, sort_keys=True, indent=4))
f.close()

t.globalcode('''
#include "document.hpp"

using namespace JVJSON_NAMESPACE_NAME;
''')

case('simple_file_read',
     'Tests reading a simple JSON file that contains all '
     'JSON element types.  No schema is used.')

t.dec('Document document;')
t.dec('bool_t result=false;')

t.exe(r'result = document.ReadFromFile("..\\..\\simple.json");')
t.chk('result==true')

t.exe(r'Element& root = document.GetRootElement();')

# Root element is a JSON object.
t.chk(r'root.GetType() == ELEMENT_TYPE_OBJECT')

# Verify boolean values are present and have the right values.
t.chk(r'root.HasElement("type_bool_true") == true')
t.exe(r'Element& trueElement = root.GetElement("type_bool_true");')
t.chk(r'trueElement.GetType() == ELEMENT_TYPE_BOOLEAN')
t.chk(r'trueElement.GetValueAsBool() == true')
t.exe(r'bool_t booleanValue = trueElement;')
t.chk(r'booleanValue == true')

t.chk(r'root.HasElement("type_bool_false") == true')
t.chk(r'root.GetElement("type_bool_false").GetType() == ELEMENT_TYPE_BOOLEAN')
#t.chk(r'root.GetElement("type_bool_false").GetValueAsBool() == false')
t.chk(r'root["type_bool_false"].GetType() == ELEMENT_TYPE_BOOLEAN')

run()
