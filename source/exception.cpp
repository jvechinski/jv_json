#include "exception.hpp"

namespace JVJSON_NAMESPACE_NAME
{

void RaiseException(const std::runtime_error& e)
{
    throw e;
}

}
