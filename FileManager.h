#pragma once
#include <string>
#include <vector>
#include "Types.h"
#include "Path.h"

namespace AssetManagement
{
	class FileManager
	{
	public:
		static const char* SPRITE_ATLAS;
		static const char* MESH_ATLAS;
		static const char* SHADERS;
		static const char* SHADER_EFFECTS;
		static const char* CONTENT_DIRECTORY;
		static const char* LOAD_PATH;

		static Common::Path getAtlasImagePath(const char* atlasName);
		static Common::Path getAtlasMetaDataPath(const char* atlasName);
		static std::vector<Common::Path> getAllFilesFromModule(const char* moduleName);
		/*
		static std::vector<std::string> getAllFilesFromDirectory(const std::string& directory);
		static std::vector<std::string> getAllFilesFromDirectory(const std::string& directory, const std::string& fileExtension);
		static bool fileExists(const std::string& path);
		static void stripDirectory(std::string& path);
		static void stripExtension(std::string& path);
		*/
	};
}
