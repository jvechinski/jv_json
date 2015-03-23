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


def read_custom_document_case(t, document=None, name='', description='', read_schema=False, schema=None):
    document_filename = create_simple_json_document(document)
    schema_filename = create_simple_json_schema(schema)
    
    case(name, description)

    t.dec('bool_t result=false;')

    if read_schema:
        t.exe(r'result = document.ReadFromFile("..\\..\\{}", '
              r'"..\\..\\{}");'.format(document_filename, schema_filename))
    else:
        t.exe(r'result = document.ReadFromFile("..\\..\\{}");'.format(
              document_filename))
              
    t.chk('result==true')

def bad_schema_case(t, schema=None, name='', description='', document=None):
    document_filename = create_simple_json_document(document)
    schema_filename = create_simple_json_schema(schema)
    
    case(name, description)

    t.dec('bool_t result=true;')

    t.exe(r'result = document.ReadFromFile("..\\..\\{}", '
          r'"..\\..\\{}");'.format(document_filename, schema_filename))
    
    t.chk('result==false')    

def good_schema_case(t, schema=None, name='', description='', document=None):
    document_filename = create_simple_json_document(document)    
    schema_filename = create_simple_json_schema(schema)
    
    case(name, description)

    t.dec('bool_t result=false;')

    t.exe(r'result = document.ReadFromFile("..\\..\\{}", '
          r'"..\\..\\{}");'.format(document_filename, schema_filename))
    
    t.chk('result==true')   

def get_simple_json_document():
    return {'type_bool_true': True,
            'type_bool_false': False,
            'type_null': None,
            'type_array': [1, 2.0, 'hello', {'deep_bool_true': True, 'deep_string': 'jv_json'}, True, False],
            'type_integer': 55, 
            'type_float': -3.14,
            'type_float_exponent': 4e-24,
            'type_string': 'world'}

def create_simple_json_file(document=None):
    if document is None:
        document = get_simple_json_document()
        filename = 'simple.json'
    else:
        document_hash = hashlib.sha1(str(document)).hexdigest()
        filename = 'simple{}.json'.format(document_hash)
    
    f = file(filename, 'w')
    f.write(json.dumps(document, sort_keys=True, indent=4))
    f.close()
    
    return filename
    
create_simple_json_document = create_simple_json_file
    
def get_simple_json_schema():
    return {'type': 'object',
            'properties': 
            {
                'type_bool_true': {'type': 'boolean'},
                'type_bool_false': {'type': 'boolean'},
                'type_null': {'type': ['number', 'null']},
                'type_array': {
                    'type': 'array',
                    'items': [
                        {'type': 'integer'},
                        {'type': 'number'},
                        {'type': 'string'},
                        {'type': 'object',
                         'properties': {
                            'deep_bool_true': {'type': 'boolean'},
                            'deep_string': {'type': 'string'},
                         }
                        }
                    ],
                    'additionalItems': {'type': 'boolean'},
                },
                'type_integer': {'type': 'integer'},
                'type_string': {'not': {'type': 'object'}},
            },            
            'additionalProperties':
            {
                'type': 'number'
            }
           }

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
