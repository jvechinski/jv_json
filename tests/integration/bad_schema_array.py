from testgen.cpp.unittest import Target, case, run

import _common

t = Target('bad_schema_array')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'not': {'type': 'array'}}
_common.bad_schema_case(t, schema,
    'bad_type', 'Type is not a match')

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3]
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'items': [{'type': 'boolean'}, 
                                                {'type': 'string'},
                                                {'type': 'null'}]}
_common.bad_schema_case(t, schema,
    'bad_tuple_form', 'Schema is "tuple" form and is invalid',
    document=document)

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3, '4']
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'items': [{'type': 'boolean'}, 
                                                {'type': 'string'},
                                                {'type': 'number'}],
                                      'additionalItems': {'type': 'integer'}}
_common.bad_schema_case(t, schema,
    'bad_tuple_with_additional_items_schema', 'Schema is "tuple" form with additionalItems schema and is invalid',
    document=document)

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3, '4']
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'items': [{'type': 'boolean'}, 
                                                {'type': 'string'},
                                                {'type': 'number'}],
                                      'additionalItems': False}
_common.bad_schema_case(t, schema,
    'bad_tuple_with_additional_items_boolean', 'Schema is "tuple" form with additionalItems set to false and is invalid',
    document=document)
    
document = _common.get_simple_json_document()
document['type_array'] = [1, 2, '3', 4]    
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'items': {'type': 'number'}}
_common.bad_schema_case(t, schema,
    'bad_list_form', 'Schema is "list" form and is invalid',
    document=document)

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3, '4', 5]
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'minItems': 6}
_common.bad_schema_case(t, schema,
    'bad_min_items', 'Minimum number of items is not acceptable',
    document=document)

schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'maxItems': 4}
_common.bad_schema_case(t, schema,
    'bad_max_items', 'Maximum number of items is acceptable',
    document=document)

schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'minItems': 2, 'maxItems': 4}
_common.bad_schema_case(t, schema,
    'bad_item_count', 'Number of items is not between minimum and maximum',
    document=document)

document = _common.get_simple_json_document()
document['type_array'] = [True, '2', 3, '4', 3, False, 1.1, 1.2]    
schema = _common.get_simple_json_schema()
schema['properties']['type_array'] = {'uniqueItems': True}
_common.bad_schema_case(t, schema,
    'bad_unique_items', 'All items in the array are not unique',
    document=document)    

run()
