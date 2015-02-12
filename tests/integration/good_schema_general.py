from testgen.cpp.unittest import Target, case, run

import _common

t = Target('good_schema_general')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['type'] = 'object'
_common.good_schema_case(t, schema,
    'good_type_1', 'Root element type is correct, single type')

schema = _common.get_simple_json_schema()
schema['type'] = ['number', 'string', 'object']
_common.good_schema_case(t, schema,
    'good_type_2', 'Root element type is correct, array of types')

schema = _common.get_simple_json_schema()
schema['properties']['type_bool_true']['type'] = 'boolean'
_common.good_schema_case(t, schema,
    'good_child_type_1', 'Child element type is correct')

schema = _common.get_simple_json_schema()
schema['properties']['type_bool_true']['type'] = ['number', 'boolean', 'null']
_common.good_schema_case(t, schema,
    'good_child_type_2', 'Child element type is correct, list of types')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'enum': ['hello', 55, True, None]}
_common.good_schema_case(t, schema,
    'good_enum_1', 'Good enum, integer matches mixed type enum')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'enum': [11,22,33,44,55,66]}
_common.good_schema_case(t, schema,
    'good_enum_2', 'Good enum, integer matches single type enum')

run()
