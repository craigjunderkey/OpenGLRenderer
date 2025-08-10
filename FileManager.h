#pragma once
#include <string>
#include <vector>
#include "Types.h"

namespace AssetManagement
{
	class FileManager
	{
	public:
		static const std::string& SPRITE_ATLAS;
		static const std::string& MESH_ATLAS;
		static const std::string& SHADERS;
		static const std::string& SHADER_EFFECTS;
		static const std::string& CONTENT_DIRECTORY;
		static const std::string& LOAD_PATH;

		static std::string getAtlasImagePath(const std::string& atlasName);
		static std::string getAtlasMetaDataPath(const std::string& atlasName);
		static std::vector<std::string> getAllFilesFromModule(const std::string& moduleName);
		static std::vector<std::string> getAllFilesFromDirectory(const std::string& directory);
		static std::vector<std::string> getAllFilesFromDirectory(const std::string& directory, const std::string& fileExtension);
		static bool fileExists(const std::string& path);
		static void stripDirectory(std::string& path);
		static void stripExtension(std::string& path);
	};
}
