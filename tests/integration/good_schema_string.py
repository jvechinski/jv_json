from testgen.cpp.unittest import Target, case, run

import _common

t = Target('good_schema_string')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_string'] = {'type': 'string'}
_common.good_schema_case(t, schema,
    'good_type', 'Type is a match')

schema = _common.get_simple_json_schema()
schema['properties']['type_string'] = {'minLength': 5}
_common.good_schema_case(t, schema,
    'good_min_length', 'Minimum length is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_string'] = {'maxLength': 5}
_common.good_schema_case(t, schema,
    'good_max_length', 'Maximum length is acceptable')

schema = _common.get_simple_json_schema()
schema['properties']['type_string'] = {'minLength': 4, 'maxLength': 6}
_common.good_schema_case(t, schema,
    'good_length', 'Length is between minimum and maximum')

run()
