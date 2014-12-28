from testgen.cpp.unittest import Target, case, run

import _common

t = Target('element_object_iterator')                               

t.globalcode(_common.global_code())

_common.read_document_case(t)

case('object_iterator',
     'Tests iterating through items in a JSON Object element.')

t.dec(r'Element& root = document.GetRootElement();')

# Verify that the root element is a JSON object.
t.chk(r'root.GetType() == ELEMENT_TYPE_OBJECT')

# Iterate through all child elements in the root element.
t.dec('uint32_t count;')
t.out('count', 0, 3)
t.exe(r'''
for (Element::Iterator i = root.Begin();
     i != root.End();
     i++)
{
    count += 1;
    printf("%s=%s\n", i.GetName().c_str(), 
        i.GetElement().GetValueAsString(true).c_str());
    printf("%s=%s\n", i.GetName().c_str(), 
        (*i).GetValueAsString(true).c_str());
}
''')

case('array_iterator',
     'Tests iterating through items in a JSON Array element.')

t.dec(r'Element& array = document.GetRootElement().GetElement("type_array");')

# Verify that the element is a JSON array.
t.chk(r'array.GetType() == ELEMENT_TYPE_ARRAY')

# Iterate through all child elements in the array element.
t.dec('uint32_t count;')
t.out('count', 0, 6)
t.exe(r'''
for (Element::Iterator i = array.Begin();
     i != array.End();
     i++)
{
    count += 1;
    printf("%d=%s\n", i.GetIndex(), 
        i.GetElement().GetValueAsString(true).c_str());
    printf("%d=%s\n", i.GetIndex(), 
        (*i).GetValueAsString(true).c_str());
}
''')

run()
