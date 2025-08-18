#include <fstream>
#include <cstring>
#include "FileManager.h"
#include "json.hpp"
#include "ErrorReporter.h"
#include "Locator.h"
#include "PathPattern.h"

using json = nlohmann::json;

using namespace AssetManagement;
using namespace Common;

const char* FileManager::SPRITE_ATLAS = "sprite_textures";
const char* FileManager::MESH_ATLAS = "mesh_textures";
const char* FileManager::SHADERS = "shaders";
const char* FileManager::SHADER_EFFECTS = "shader_effects";
const char* FileManager::CONTENT_DIRECTORY = "Content/";
const char* FileManager::LOAD_PATH = "Content/load.json";

Path FileManager::getAtlasImagePath(const char* atlasName)
{
	return Path::makePreformatted(std::move(
		String::concatenate(CONTENT_DIRECTORY, atlasName) + ".atlas.png"
	));
}

Path FileManager::getAtlasMetaDataPath(const char* atlasName)
{
	return Path::makePreformatted(std::move(
		String::concatenate(CONTENT_DIRECTORY, atlasName) + ".atlas"
	));
}

std::vector<Path> FileManager::getAllFilesFromModule(const char* moduleName)
{
	std::ifstream file = std::ifstream(FileManager::LOAD_PATH);
	json data = json::parse(file);
	std::vector<Path> filePaths;

	for (auto& element : data[moduleName])
	{
		Path path = Path(static_cast<std::string>(element).data());
		
		if (path.isPattern())
		{
			PathPattern pattern = path.makePattern();
			
			if (!pattern.extension.has_value())
			{
				// * appears at the end, so simply include all files in this directory
				std::vector<Path> filesFound = std::move(
					Locator::fileSystem().getFilesInDirectory(pattern.directory)
				);
				filePaths.insert(filePaths.end(), filesFound.begin(), filesFound.end());
			}
			else
			{
				// * appears before a file extension, so include all files of this extension
				std::vector<Path> filesFound = std::move(
					Locator::fileSystem().getFilesInDirectory(pattern.directory, pattern.extension.value().data())
				);
				filePaths.insert(filePaths.end(), filesFound.begin(), filesFound.end());
			}
		}
		else
		{
			filePaths.push_back(path);
		}
	}

	return filePaths;
}

/*
std::vector<std::string> FileManager::getAllFilesFromDirectory(const std::string& directory)
{
	std::vector<std::string> filePaths;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
	{
		filePaths.push_back(entry.path().generic_string());
	}

	return filePaths;
}

std::vector<std::string> FileManager::getAllFilesFromDirectory(const std::string& directory, const std::string& extension)
{
	std::vector<std::string> filePaths;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
	{
		std::string pathString = entry.path().generic_string();
		if (pathString.ends_with(extension))
			filePaths.push_back(pathString);
	}

	return filePaths;
}

bool FileManager::fileExists(const std::string& path)
{
	return std::filesystem::exists(path);
}

void FileManager::stripDirectory(std::string& path)
{
	i32 slashIndex = path.find_last_of("/\\");
	if (slashIndex != std::string::npos)
		path = std::move(path.substr(slashIndex + 1, path.length() - slashIndex));
}

void FileManager::stripExtension(std::string& path)
{
	i32 extensionIndex = path.find_last_of('.');
	if (extensionIndex != std::string::npos)
		path = std::move(path.substr(0, extensionIndex));
}
*/