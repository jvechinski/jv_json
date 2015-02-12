from testgen.cpp.unittest import Target, case, run

import _common

t = Target('bad_schema_object')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema = {'not': {'type': 'object'}}
_common.bad_schema_case(t, schema,
    'bad_type', 'Type is not a match')
   
document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'carrot': True, 'donut': 'false'}
schema = _common.get_simple_json_schema()
schema = {'properties': {'apple': {'type': 'integer'}, 
                         'banana': {'type': 'number'},
                         'carrot': {'type': 'boolean'}},
          'additionalProperties': False}
_common.bad_schema_case(t, schema,
    'bad_object_with_additional_properties', 'Schema has additionalProperties set to false and is invalid',
    document=document)
    
document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'carrot': True, 'donut': 'false', 'eel': None}
schema = _common.get_simple_json_schema()
schema = {'minProperties': 6}
_common.bad_schema_case(t, schema,
    'bad_min_properties', 'Minimum number of properties is not acceptable',
    document=document)

schema = _common.get_simple_json_schema()
schema = {'maxProperties': 4}
_common.bad_schema_case(t, schema,
    'bad_max_properties', 'Maximum number of properties is not acceptable',
    document=document)

schema = _common.get_simple_json_schema()
schema = {'minProperties': 2, 'maxProperties': 4}
_common.bad_schema_case(t, schema,
    'bad_property_count', 'Number of properties is outside minimum and maximum',
    document=document)
    
document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'donut': 'false'}
schema = _common.get_simple_json_schema()
schema = {'properties': {'apple': {'type': 'integer'}, 
                         'banana': {'type': 'number'},
                         'carrot': {'type': 'boolean'}},
          'required': ['apple', 'banana', 'carrot']}
_common.bad_schema_case(t, schema,
    'bad_object_required_properties', 'One required property missing',
    document=document)
   
document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'carrot': True, 'donut': 'false'}
schema = _common.get_simple_json_schema()
schema = {'properties': {'apple': {'type': 'integer'}, 
                         'carrot': {'type': 'boolean'},
                         'banana': {'type': 'number'}},
          'dependencies': {'apple': ['eel', 'carrot']}}
_common.bad_schema_case(t, schema,
    'bad_object_dependent_properties', 'A dependent property is missing',
    document=document)    

run()
