from testgen.cpp.unittest import Target, case, run

import _common

t = Target('good_schema_string')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'type': 'array'}
_common.good_schema_case(t, schema,
    'good_type', 'Type is a match')

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3]
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'items': [{'type': 'boolean'}, 
                                                {'type': 'string'},
                                                {'type': 'number'}]}
_common.good_schema_case(t, schema,
    'good_tuple_form', 'Schema is "tuple" form and is valid',
    document=document)

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3, '4']
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'items': [{'type': 'boolean'}, 
                                                {'type': 'string'},
                                                {'type': 'number'}],
                                      'additionalItems': {'type': 'string'}}
_common.good_schema_case(t, schema,
    'good_tuple_with_additional_items_schema', 'Schema is "tuple" form with additionalItems schema and is valid',
    document=document)

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3, '4']
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'items': [{'type': 'boolean'}, 
                                                {'type': 'string'},
                                                {'type': 'number'}],
                                      'additionalItems': True}
_common.good_schema_case(t, schema,
    'good_tuple_with_additional_items_boolean', 'Schema is "tuple" form with additionalItems set to true and is valid',
    document=document)
    
document = _common.get_simple_json_document()
document['type_array'] = [1, 2, 3, 4]    
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'items': {'type': 'number'}}
_common.good_schema_case(t, schema,
    'good_list_form', 'Schema is "list" form and is valid',
    document=document)

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3, '4', 5]
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'minItems': 5}
_common.good_schema_case(t, schema,
    'good_min_items', 'Minimum number of items is acceptable',
    document=document)

schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'maxItems': 5}
_common.good_schema_case(t, schema,
    'good_max_items', 'Maximum number of items is acceptable',
    document=document)

schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'minItems': 4, 'maxItems': 6}
_common.good_schema_case(t, schema,
    'good_item_count', 'Number of items is between minimum and maximum',
    document=document)

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3, '4', 5, False, 1.1, 1.2]    
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'uniqueItems': True}
_common.good_schema_case(t, schema,
    'good_unique_items', 'All items in the array are unique',
    document=document)    

run()
