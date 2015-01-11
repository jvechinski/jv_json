#include "element_number.hpp"

namespace JVJSON_NAMESPACE_NAME
{

bool_t ElementNumber::IsValue(void) const
{
    return true;
}
    
bool_t ElementNumber::IsNumber(void) const
{
    return true;    
}
       
};
