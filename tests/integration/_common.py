from testgen.cpp.unittest import case
import json
import hashlib

def global_code():
    return r'''
#include "document.hpp"

using namespace JVJSON_NAMESPACE_NAME;

Document document;
'''


def read_document_case(t, read_schema=False):
    create_simple_json_file()
    if read_schema:
        create_simple_json_schema()
    
    case('read_document',
         'Tests reading a simple JSON file that contains all '
         'JSON element types.')

    t.dec('bool_t result=false;')

    if read_schema:
        t.exe(r'result = document.ReadFromFile("..\\..\\simple.json", "..\\..\\simple.schema.json");')
    else:
        t.exe(r'result = document.ReadFromFile("..\\..\\simple.json");')
    t.chk('result==true')

def bad_schema_case(t, bad_schema=None, name='', description=''):
    create_simple_json_file()
    schema_filename = create_simple_json_schema(bad_schema)
    
    case(name, description)

    t.dec('bool_t result=true;')

    t.exe(r'result = document.ReadFromFile("..\\..\\simple.json", '
          r'"..\\..\\{}");'.format(schema_filename))
    
    t.chk('result==false')    

def create_simple_json_file():
    f = file('simple.json', 'w')
    f.write(json.dumps({'type_bool_true': True,
                        'type_bool_false': False,
                        'type_null': None,
                        'type_array': [1, 2.0, 'hello', True, False, {'deep_bool_true': True, 'deep_string': 'jv_json'}],
                        'type_integer': 5, 
                        'type_float': -3.14,
                        'type_float_exponent': 4e-24,
                        'type_string': 'world'}, 
                       sort_keys=True, indent=4))
    f.close()
    
def get_simple_json_schema():
    return {'type': 'object'}

def create_simple_json_schema(schema=None):
    if schema is None:
        schema = get_simple_json_schema()
        filename = 'simple.schema.json'
    else:
        schema_hash = hashlib.sha1(str(schema)).hexdigest()
        filename = 'simple.schema{}.json'.format(schema_hash)
    
    f = file(filename, 'w')
    f.write(json.dumps(schema, sort_keys=True, indent=4))
    f.close()
    
    return filename
