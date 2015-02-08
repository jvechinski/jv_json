from testgen.cpp.unittest import Target, case, run

import _common

t = Target('bad_schema_string')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_string'] = {'not': {'type': 'string'}}
_common.bad_schema_case(t, schema,
    'bad_type', 'Bad type for a string')

schema = _common.get_simple_json_schema()
schema['properties']['type_string'] = {'minLength': 6}
_common.bad_schema_case(t, schema,
    'bad_minimum_length', 'Bad minLength for a string (string to small)')

schema = _common.get_simple_json_schema()
schema['properties']['type_string'] = {'maxLength': 4}
_common.bad_schema_case(t, schema,
    'bad_maximum_length', 'Bad maxLength for a string (string to large)')

run()
