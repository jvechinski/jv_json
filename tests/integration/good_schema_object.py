from testgen.cpp.unittest import Target, case, run

import _common

t = Target('good_schema_object')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['type'] = {'type': 'object'}
_common.good_schema_case(t, schema,
    'good_type', 'Type is a match')

document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'carrot': True, 'donut': 'false'}
schema = _common.get_simple_json_schema()
schema = {'properties': {'apple': {'type': 'integer'}, 
                         'banana': {'type': 'number'},
                         'carrot': {'type': 'boolean'}},
          'additionalProperties': True}
_common.good_schema_case(t, schema,
    'good_object_with_additional_properties_boolean_1', 'Schema has additionalProperties set to true and is valid',
    document=document)
    
document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'carrot': True}
schema = _common.get_simple_json_schema()
schema = {'properties': {'apple': {'type': 'integer'}, 
                         'banana': {'type': 'number'},
                         'carrot': {'type': 'boolean'}},
          'additionalProperties': False}
_common.good_schema_case(t, schema,
    'good_object_with_additional_properties_boolean_2', 'Schema has additionalProperties set to false and is valid',
    document=document)
    
document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'carrot': True, 'donut': 'false', 'eel': None}
schema = _common.get_simple_json_schema()
schema = {'minProperties': 5}
_common.good_schema_case(t, schema,
    'good_min_properties', 'Minimum number of properties is acceptable',
    document=document)

schema = _common.get_simple_json_schema()
schema = {'maxProperties': 5}
_common.good_schema_case(t, schema,
    'good_max_properties', 'Maximum number of properties is acceptable',
    document=document)

schema = _common.get_simple_json_schema()
schema = {'minProperties': 4, 'maxProperties': 6}
_common.good_schema_case(t, schema,
    'good_property_count', 'Number of properties is between minimum and maximum',
    document=document)
    
document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'carrot': True}
schema = _common.get_simple_json_schema()
schema = {'properties': {'apple': {'type': 'integer'}, 
                         'banana': {'type': 'number'},
                         'carrot': {'type': 'boolean'}},
          'required': ['apple', 'banana', 'carrot']}
_common.good_schema_case(t, schema,
    'good_object_required_properties_1', 'All required properties present',
    document=document)

document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'carrot': True}
schema = _common.get_simple_json_schema()
schema = {'properties': {'apple': {'type': 'integer'}, 
                         'carrot': {'type': 'boolean'},
                         'banana': {'type': 'number'}},
          'required': ['apple', 'carrot']}
_common.good_schema_case(t, schema,
    'good_object_required_properties_2', 'All required properties present plus some not required',
    document=document)
    
document = _common.get_simple_json_document()
document = {'apple': 1, 'banana': 2.0, 'carrot': True, 'donut': 'false'}
schema = _common.get_simple_json_schema()
schema = {'properties': {'apple': {'type': 'integer'}, 
                         'carrot': {'type': 'boolean'},
                         'banana': {'type': 'number'}},
          'dependencies': {'apple': ['donut', 'carrot']}}
_common.good_schema_case(t, schema,
    'good_object_dependent_properties_1', 'All dependent properties present',
    document=document)    

document = _common.get_simple_json_document()
document = {'banana': 2.0, 'carrot': True}
schema = _common.get_simple_json_schema()
schema = {'properties': {'apple': {'type': 'integer'}, 
                         'carrot': {'type': 'boolean'},
                         'banana': {'type': 'number'}},
          'dependencies': {'apple': ['donut', 'carrot']}}
_common.good_schema_case(t, schema,
    'good_object_dependent_properties_2', 'Parent property not present, so dependencies are not processed',
    document=document)    

run()
