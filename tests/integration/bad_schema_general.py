from testgen.cpp.unittest import Target, case, run

import _common

t = Target('bad_schema_general')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['type'] = 'array'
_common.bad_schema_case(t, schema,
    'bad_type_1', 'Root element type is incorrect, single type')

schema = _common.get_simple_json_schema()
schema['type'] = ['number', 'string', 'boolean']
_common.bad_schema_case(t, schema,
    'bad_type_2', 'Root element type is incorrect, array of types')

run()
