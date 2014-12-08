from testgen.cpp.unittest import Target, case, run

t = Target('simple_file_read_no_schema')                               

import json
f = file('simple.json', 'w')
f.write(json.dumps({'4': 5, '6': 7}, sort_keys=True, indent=4))
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

run()
