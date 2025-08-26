#include "Core/Utils/FileSystem.hpp"
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"
#include <filesystem>
#include <ios>

namespace WB
{

bool FileSystem::SyncReadAtPathAsString(const Path& path, std::string& outData)
{
    WB_CORE_ASSERT(!path.empty(), "path is empty");

    File file;
    if(OpenFile(path, file, FileMode::FILE_MODE_READ_BINARY))
    {
        size_t bufferSize = GetFileSize(file);

        outData.resize(bufferSize);

        size_t rBytesRead;
        bool result = SyncReadFileAsByte(file, &outData[0], bufferSize, rBytesRead);
        CloseFile(file);

        if(result)
        {
            return true;
        }
    }

    CORE_LOG_ERROR("Failed to read file as string : %s", path.string().c_str());
    return false;
}

bool FileSystem::SyncWriteAtPathAsString(const Path& path, const std::string& data)
{
    WB_CORE_ASSERT(!path.empty(), "path is empty");

    File file;
    if(OpenFile(path, file, FileMode::FILE_MODE_WRITE_BINARY))
    {
        size_t bufferSize = GetFileSize(file);

        size_t rBytesRead;
        bool result = SyncWriteFileAsByte(file, data.c_str());
        CloseFile(file);

        if(result)
        {
            return true;
        }
    }

    CORE_LOG_ERROR("Failed to write file as string : %s", path.string().c_str());
    return false;
}

bool FileSystem::CreateFolder(const Path& path, const std::string& name)
{
    return std::filesystem::create_directory(path / name);
}

bool FileSystem::SyncReadFileAsByte(File& file, char* outBuffer, size_t bufferSize, size_t& outrBytesRead)
{
    WB_CORE_ASSERT(outBuffer != nullptr, "path is nullptr");

    file.handle.read(outBuffer, bufferSize);

    std::streamsize size = file.handle.gcount();

    if(file.handle)
    {
        outrBytesRead = size;
        return true;
    }

    outrBytesRead = 0;
    CORE_LOG_ERROR("Failed to read all byte, read size : %zu, file : %s", size, file.path.c_str());
    return false;
}

bool FileSystem::SyncWriteFileAsByte(File& file, const char* buffer)
{
    file.handle << buffer;
    if(file.handle)
    {
        return true;
    }

    return false;
}

bool FileSystem::OpenFile(const Path& path, File& outFile, FileMode mode)
{
    WB_CORE_ASSERT(!path.empty(), "path is empty");

	int openMode = std::ios::in;

	switch (mode)
	{
        case FileMode::FILE_MODE_READ:
		openMode = std::ios::in;
		break;
	case FileMode::FILE_MODE_READ_BINARY:
		openMode = std::ios::in | std::ios::binary;
		break;
	case FileMode::FILE_MODE_WRITE:
		openMode = std::ios::out;
		break;
	case FileMode::FILE_MODE_WRITE_BINARY:
		openMode = std::ios::out | std::ios::binary;
		break;
	default:
		CORE_LOG_ERROR("failed to use the file mode, 'FILE_MODE_READ' mode will be used by default");
		break;
    }

    outFile.handle = std::fstream(path, openMode);
    outFile.path = path;

    if(!outFile.handle.is_open())
    {
        CORE_LOG_ERROR("failed to open file %s", path.string().c_str());
        return false;
    }

    return true;
}

void FileSystem::CloseFile(File& file)
{
    file.handle.close();
}

size_t FileSystem::GetFileSize(File& file)
{
    file.handle.seekg(0, std::ios::end);
    size_t bufferSize = file.handle.tellg();
    file.handle.seekg(0, std::ios::beg);
    return static_cast<size_t>(bufferSize);
}

}
