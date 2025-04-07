#pragma once
#include "Core/Core.hpp"

namespace WB
{

class FileSystem
{
public:
    [[nodiscard]] static bool GetFileAsChar(const char* path, std::string& outData);

private:
    [[nodiscard]] static bool OpenFile(const std::filesystem::path& path, std::ifstream& outStream);
};

}
