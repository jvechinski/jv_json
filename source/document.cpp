#include "document.hpp"
#include "cJSON/cJSON.h"

#include <fstream>

namespace JVJSON_NAMESPACE_NAME
{

Element* Document::GetRootElement(void)
{
    return this->rootElement;
}

bool_t Document::ReadFromFile(const char* filename, const char* schemaFilename)
{
    printf("Parsing file %s\n", filename);
    
    std::ifstream infile;
    infile.open(filename);
    
    if (!infile.is_open())
    {
        return false;
    }
    
    infile.seekg(0, std::ios::end);
    
    size_t size = infile.tellg();
    char* buffer = new char[size];
    
    infile.seekg(0);
    infile.read(&buffer[0], size);    
    
    cJSON *root = cJSON_Parse(buffer);
    
    printf("Parsed file, root pointer 0x%x\n", (uint32_t)root);
    
    delete buffer;
    
    cJSON_Delete(root);
    
    return true;
}    
    
}
