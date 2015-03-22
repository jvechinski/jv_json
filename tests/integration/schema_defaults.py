from testgen.cpp.unittest import Target, case, run

import _common

t = Target('schema_defaults')                               

t.globalcode(_common.global_code())

schema = _common.get_simple_json_schema()
schema['properties']['type_default'] = {'type': 'integer', 'default': 1234}
_common.good_schema_case(t, schema,
    'good_object_default_simple', 'Simple default value for an object property') 
# Check that an element exists for the specified default.
t.dec('bool hasElement = false;')
t.exe('hasElement = document.GetRootElement().HasElement("type_default");')
t.chk('hasElement==true')
# Check that the default element has the proper default value.
t.dec('int32_t defaultValue = 0;')
t.exe('defaultValue = document.GetRootElement().GetElement("type_default").GetValueAsInt32();')
t.chk('defaultValue==1234')

schema = _common.get_simple_json_schema()
schema['properties']['type_default'] = {'type': 'object', 'default': {'my_default': 5050}}
_common.good_schema_case(t, schema,
    'good_object_default_complex', 'Complex (container type) default value for an object property') 
# Check that an element exists for the specified default.
t.dec('bool hasElement = false;')
t.exe('hasElement = document.GetRootElement().HasElement("type_default");')
t.chk('hasElement==true')
# Check that the default element has the proper default value.
t.dec('int32_t defaultValue = 0;')
t.exe('defaultValue = document.GetRootElement().GetElement("type_default").GetElement("my_default").GetValueAsInt32();')
t.chk('defaultValue==5050')

schema = _common.get_simple_json_schema()
schema['properties']['type_default'] = {'type': 'integer', 'default': 'hello!'}
_common.bad_schema_case(t, schema,
    'bad_object_default', 'Bad default value for an object property, does not fit schema') 

schema = _common.get_simple_json_schema()
schema['properties']['type_array']['items'] = \
    [{'type': 'number'}, {'type': 'string'}, {'type': 'integer', 'default': 1234}]
document = _common.get_simple_json_document()
document['type_array'] = [1, 'hello']
_common.good_schema_case(t, schema,
    'good_array_default_simple', 'Simple default value for an array index', 
    document=document) 
# Check that an element exists for the specified default.
t.dec('bool hasElement = false;')
t.exe('hasElement = document.GetRootElement().GetElement("type_array").HasElement(2);')
t.chk('hasElement==true')
t.dec('uint32_t arraySize = 0;')
t.exe('arraySize = document.GetRootElement().GetElement("type_array").GetSize();')
t.chk('arraySize==3')
# Check that the default element has the proper default value.
t.dec('int32_t defaultValue;')
t.exe('defaultValue = document.GetRootElement().GetElement("type_array").GetElement(2).GetValueAsInt32();')
t.chk('defaultValue==1234')

schema = _common.get_simple_json_schema()
schema['properties']['type_array']['items'] = \
    [{'type': 'number'}, {'type': 'string'}, {'type': 'object', 'default': {'my_default': 5050}}]
document = _common.get_simple_json_document()
document['type_array'] = [1, 'hello']
_common.good_schema_case(t, schema,
    'good_array_default_simple', 'Complex (container type) default value for an array index', 
    document=document) 
# Check that an element exists for the specified default.
t.dec('bool hasElement = false;')
t.exe('hasElement = document.GetRootElement().GetElement("type_array").HasElement(2);')
t.chk('hasElement==true')
t.dec('uint32_t arraySize = 0;')
t.exe('arraySize = document.GetRootElement().GetElement("type_array").GetSize();')
t.chk('arraySize==3')
# Check that the default element has the proper default value.
t.dec('int32_t defaultValue;')
t.exe('defaultValue = document.GetRootElement().GetElement("type_array").GetElement(2).GetElement("my_default").GetValueAsInt32();')
t.chk('defaultValue==5050')

schema = _common.get_simple_json_schema()
schema['properties']['type_array']['items'] = \
    [{'type': 'number'}, {'type': 'string'}, {'type': 'integer', 'default': 'hello!'}]
document = _common.get_simple_json_document()
document['type_array'] = [1, 'hello']
_common.bad_schema_case(t, schema,
    'bad_array_default', 'Bad default value for an array index, does not fit schema',
    document=document) 

run()
