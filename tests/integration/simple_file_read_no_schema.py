from testgen.cpp.unittest import Target, case, run

import _common

t = Target('simple_file_read_no_schema')                               

t.globalcode('#include <cstring>\n'+_common.global_code())

_common.read_document_case(t)

case('check_document_contents',
     'Verifies that the document contains all the expected Elements')

t.exe(r'Element& root = document.GetRootElement();')

# Root element is a JSON object.
t.chk(r'root.GetType() == ELEMENT_TYPE_OBJECT')
t.chk(r'root.IsContainer() == true')

# Verify boolean values are present and have the right values.
# true
t.chk(r'root.HasElement("type_bool_true") == true')
t.exe(r'Element& trueElement = root.GetElement("type_bool_true");')
t.chk(r'trueElement.GetType() == ELEMENT_TYPE_BOOLEAN')
t.chk(r'trueElement.GetValueAsBool() == true')
t.chk(r'trueElement.IsValue() == true')
t.exe(r'bool_t booleanValue = trueElement;')
t.chk(r'booleanValue == true')
# false
t.chk(r'root.HasElement("type_bool_false") == true')
t.chk(r'root.GetElement("type_bool_false").GetType() == ELEMENT_TYPE_BOOLEAN')
t.chk(r'root.GetElement("type_bool_false").GetValueAsBool() == false')
t.chk(r'root["type_bool_false"].GetType() == ELEMENT_TYPE_BOOLEAN')

# Check for the null element.
t.chk(r'root.HasElement("type_null") == true')
t.chk(r'root.GetElement("type_null").GetType() == ELEMENT_TYPE_NULL')
t.chk(r'root.GetElement("type_null").IsNull() == true')
t.chk(r'root.GetElement("type_null").IsValue() == false')

# Verify integer value is present.
t.chk(r'root.HasElement("type_integer") == true')
t.exe(r'Element& integerElement = root.GetElement("type_integer");')
t.chk(r'integerElement.GetType() == ELEMENT_TYPE_INTEGER')
t.chk(r'integerElement.GetValueAsUint32() == 55U')
t.chk(r'integerElement.IsValue() == true')
t.chk(r'integerElement.IsNumber() == true')

# Verify floating point values are present and have the right values.
# decimal point
t.chk(r'root.HasElement("type_float") == true')
t.exe(r'Element& floatElement = root.GetElement("type_float");')
t.chk(r'floatElement.GetType() == ELEMENT_TYPE_FLOAT')
t.chk(r'floatElement.GetValueAsFloat64() > -3.15')
t.chk(r'floatElement.GetValueAsFloat64() < -3.13')
t.chk(r'floatElement.IsValue() == true')
t.chk(r'integerElement.IsNumber() == true')
# exponent
t.chk(r'root.HasElement("type_float_exponent") == true')
t.chk(r'root.GetElement("type_float_exponent").GetType() == ELEMENT_TYPE_FLOAT')

# Verify string value is present.
t.chk(r'root.HasElement("type_string") == true')
t.exe(r'Element& stringElement = root.GetElement("type_string");')
t.chk(r'stringElement.GetType() == ELEMENT_TYPE_STRING')
t.chk(r'strcmp(stringElement.GetValueAsString().c_str(), "world")==0', fmt=None)
t.chk(r'stringElement.IsValue() == true')
t.chk(r'stringElement.IsNumber() == false')

run()
