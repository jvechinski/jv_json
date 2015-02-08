from testgen.cpp.unittest import Target, case, run

import _common

t = Target('good_schema_float')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'type': 'number'}
_common.good_schema_case(t, schema,
    'good_type', 'Type is a match')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'minimum': -3.14}
_common.good_schema_case(t, schema,
    'good_minimum', 'Minimum value is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'minimum': -3.15, 'exclusiveMinimum': True}
_common.good_schema_case(t, schema,
    'good_exclusive_minimum', 'Exclusive minimum value is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'maximum': -3.14}
_common.good_schema_case(t, schema,
    'good_maximum', 'Maximum value is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'maximum': -3.13, 'exclusiveMaximum': True}
_common.good_schema_case(t, schema,
    'good_exclusive_maximum', 'Exclusive maximum value is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_float'] = {'multipleOf': 3.14}
_common.good_schema_case(t, schema,
    'good_multiple_of', 'Value is a multiple of the specified value')

run()
