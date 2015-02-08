from testgen.cpp.unittest import Target, case, run

import _common

t = Target('bad_schema_float')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'not': {'type': 'number'}}
_common.bad_schema_case(t, schema,
    'bad_type', 'Type is not a match')
    
schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'not': {'type': 'integer'}}
_common.bad_schema_case(t, schema,
    'bad_type_2', 'Type is not a match')    

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'minimum': 56}
_common.bad_schema_case(t, schema,
    'bad_minimum', 'Minimum value is too high')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'minimum': 55, 'exclusiveMinimum': True}
_common.bad_schema_case(t, schema,
    'bad_exclusive_minimum', 'Exclusive minimum value too high')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'maximum': 54}
_common.bad_schema_case(t, schema,
    'bad_maximum', 'Maximum value is too low')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'maximum': 55, 'exclusiveMaximum': True}
_common.bad_schema_case(t, schema,
    'bad_exclusive_maximum', 'Exclusive maximum value is too low')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'multipleOf': 10}
_common.bad_schema_case(t, schema,
    'bad_multiple_of', 'Value is not a multiple of the specified value')

run()
