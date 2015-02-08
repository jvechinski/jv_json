from testgen.cpp.unittest import Target, case, run

import _common

t = Target('bad_schema_float')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'not': {'type': 'number'}}
_common.bad_schema_case(t, schema,
    'bad_type', 'Type is not a match')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'minimum': -3.13}
_common.bad_schema_case(t, schema,
    'bad_minimum', 'Minimum value is too high')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'minimum': -3.14, 'exclusiveMinimum': True}
_common.bad_schema_case(t, schema,
    'bad_exclusive_minimum', 'Exclusive minimum value too high')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'maximum': -3.15}
_common.bad_schema_case(t, schema,
    'bad_maximum', 'Maximum value is too low')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'maximum': -3.14, 'exclusiveMaximum': True}
_common.bad_schema_case(t, schema,
    'bad_exclusive_maximum', 'Exclusive maximum value is too low')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'multipleOf': 3.13}
_common.bad_schema_case(t, schema,
    'bad_multiple_of', 'Value is not a multiple of the specified value')

run()
