from testgen.cpp.unittest import Target, case, run

import _common

t = Target('document_iterator')                               

t.globalcode(_common.global_code())

_common.read_document_case(t)

case('document_iterator',
     'Tests iterating through items in a JSON document.')

# Iterate through all child elements in the root element.
t.dec('uint32_t count;')
t.out('count', 0, 12)
t.exe(r'''
for (Document::Iterator i = document.Begin();
     i != document.End();
     i++)
{
    count += 1;
    printf("%s (depth %d)=%s\n", i.GetElement().GetAddress().c_str(), 
        i.GetDepth(),
        i.GetElement().GetValueAsString(true).c_str());
}
''')

case('document_iterator',
     'Tests iterating through items in a JSON document, using the '
    'include parent end state.')

# Iterate through all child elements in the root element.
t.dec('uint32_t count;')
t.out('count', 0, 15)
t.exe(r'''
for (Document::Iterator i = document.Begin(true);
     i != document.End();
     i++)
{
    count += 1;
    printf("%s (depth %d) (parent end %d)=%s\n", (*i).GetAddress().c_str(), 
        i.GetDepth(),
        i.IsParentEndState(),
        (*i).GetValueAsString(true).c_str());
}
''')

run()
