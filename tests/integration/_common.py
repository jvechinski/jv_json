from testgen.cpp.unittest import case
import json

def global_code():
    return r'''
#include "document.hpp"

using namespace JVJSON_NAMESPACE_NAME;

Document document;
'''


def read_document_case(t, read_schema=False):
    create_simple_json_file()
    
    case('read_document',
         'Tests reading a simple JSON file that contains all '
         'JSON element types.')

    t.dec('bool_t result=false;')

    t.exe(r'result = document.ReadFromFile("..\\..\\simple.json");')
    t.chk('result==true')
    

def create_simple_json_file():
    f = file('simple.json', 'w')
    f.write(json.dumps({'type_bool_true': True,
                        'type_bool_false': False,
                        'type_null': None,
                        'type_array': [1, 2.0, 'hello', True, False, {'deep_bool_true': True, 'deep_string': 'jv_json'}],
                        'type_integer': 5, 
                        'type_float': -3.14,
                        'type_float_exponent': 4e-24,
                        'type_string': 'world'}, sort_keys=True, indent=4))
    f.close()
