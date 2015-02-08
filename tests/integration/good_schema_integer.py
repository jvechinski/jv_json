from testgen.cpp.unittest import Target, case, run

import _common

t = Target('good_schema_integer')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'type': 'number'}
_common.good_schema_case(t, schema,
    'good_type', 'Type is a match')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'type': 'integer'}
_common.good_schema_case(t, schema,
    'good_type_2', 'Type is a match')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'minimum': 55}
_common.good_schema_case(t, schema,
    'good_minimum', 'Minimum value is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'minimum': 54, 'exclusiveMinimum': True}
_common.good_schema_case(t, schema,
    'good_exclusive_minimum', 'Exclusive minimum value is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'maximum': 55}
_common.good_schema_case(t, schema,
    'good_maximum', 'Maximum value is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'maximum': 56, 'exclusiveMaximum': True}
_common.good_schema_case(t, schema,
    'good_exclusive_maximum', 'Exclusive maximum value is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'multipleOf': 11}
_common.good_schema_case(t, schema,
    'good_multiple_of', 'Value is a multiple of the specified value')

run()
