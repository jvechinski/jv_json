from testgen.cpp.unittest import Target, case, run

import _common

t = Target('good_schema_compounds')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_integer']['type'] = {'not': {'type': 'string'}}
_common.good_schema_case(t, schema,
    'good_not', 'Use not compound')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer']['type'] = {'anyOf': [{'type': 'string'}, {'type': 'number'}, {'type': 'null'}]}
_common.good_schema_case(t, schema,
    'good_any_of', 'Use anyOf compound')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer']['type'] = {'oneOf': [{'type': 'string'}, {'type': 'null'}, {'type': 'integer'}]}
_common.good_schema_case(t, schema,
    'good_one_of', 'Use oneOf compound')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer']['type'] = {'allOf': [{'type': 'number'}, {'type': 'integer'}]}
_common.good_schema_case(t, schema,
    'good_all_of', 'Use allOf compound')

schema = _common.get_simple_json_schema()
schema['properties']['type_integer']['type'] = {'allOf': [{'not': {'type': 'string'}}, {'anyOf': [{'type': 'string'}, {'type': 'number'}, {'type': 'null'}]}, {'oneOf': [{'type': 'string'}, {'type': 'null'}, {'type': 'integer'}]}]}
_common.good_schema_case(t, schema,
    'good_nested', 'Use nested compounds')

run()
