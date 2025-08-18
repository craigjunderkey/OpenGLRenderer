#include <filesystem>
#include "DesktopFileSystem.h"

using namespace Common;

std::vector<Path> DesktopFileSystem::getFilesInImmediateDirectory(const Path& directory)
{
	std::vector<Path> filePaths;

	for (const auto& entry : std::filesystem::directory_iterator(directory.path().data()))
	{
		filePaths.push_back(Path(entry.path().generic_string().data()));
	}

	return filePaths;
}

std::vector<Path> DesktopFileSystem::getFilesInDirectory(const Path& directory)
{
	std::vector<Path> filePaths;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(directory.path().data()))
	{
		filePaths.push_back(Path(entry.path().generic_string().data()));
	}

	return filePaths;
}

std::vector<Path> DesktopFileSystem::getFilesInDirectory(const Path& directory, const char* extension)
{
	std::vector<Path> filePaths;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(directory.path().data()))
	{
		std::cout << entry.path().generic_string().data() << std::endl;
		Path path = Path(entry.path().generic_string().data());
		
		if (path.extensionMatches(extension))
			filePaths.push_back(std::move(path));
	}

	return filePaths;
}

bool DesktopFileSystem::fileExists(const Path& file)
{
	return std::filesystem::exists(file.path().data());
}