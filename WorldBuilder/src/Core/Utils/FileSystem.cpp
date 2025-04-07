#include "Core/Utils/FileSystem.hpp"
#include "Core/Log/Log.hpp"

namespace WB
{

bool FileSystem::GetFileAsChar(const char* path, std::string& outData)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if(!file.is_open())
    {
        CORE_LOG_ERROR("failed to open file %s", path);
        return false;
    }

    file.seekg(0, std::ios::end);
    outData.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&outData[0], outData.size());
    file.close();

    return true;
}

bool FileSystem::OpenFile(const std::filesystem::path& path, std::ifstream& outStream)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        CORE_LOG_ERROR("Failed to open file : %s", path.c_str());
        return false;
    }
    return true;
}

}
