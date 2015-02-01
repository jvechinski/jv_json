from testgen.cpp.unittest import Target, case, run

import _common

t = Target('bad_schema_compounds')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'not': {'type': 'integer'}}
_common.bad_schema_case(t, schema,
    'bad_not', 'Bad not compound')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'anyOf': [{'type': 'string'}, {'type': 'boolean'}, {'type': 'null'}]}
_common.bad_schema_case(t, schema,
    'bad_any_of', 'Bad anyOf compound, none are true')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'oneOf': [{'type': 'string'}, {'type': 'null'}, {'type': 'object'}]}
_common.bad_schema_case(t, schema,
    'bad_one_of1', 'Bad oneOf compound, none are true')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'oneOf': [{'type': 'number'}, {'type': 'null'}, {'type': 'integer'}]}
_common.bad_schema_case(t, schema,
    'bad_one_of2', 'Bad oneOf compound, more than 1 are true')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'allOf': [{'type': 'array'}, {'type': 'number'}, {'type': 'integer'}]}
_common.bad_schema_case(t, schema,
    'bad_all_of1', 'Bad allOf compound, 1 is not true')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer'] = {'allOf': [{'type': 'array'}, {'type': 'object'}, {'type': 'string'}]}
_common.bad_schema_case(t, schema,
    'bad_all_of2', 'Bad allOf compound, none are true')

run()
