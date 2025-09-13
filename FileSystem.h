#pragma once
#include <vector>
#include "Path.h"

namespace Common
{
	class FileSystem
	{
	public:
		virtual std::vector<Path> getFilesInImmediateDirectory(const Path& directory) = 0;
		virtual std::vector<Path> getFilesInDirectory(const Path& directory) = 0;
		virtual std::vector<Path> getFilesInDirectory(const Path& directory, const char* extension) = 0;
		
		virtual bool fileExists(const Path& file) = 0;
		
		virtual void createDirectory(const Path& directory) = 0;
		virtual void destroyDirectory(const Path& directory) = 0;

		virtual ~FileSystem() = default;
	};
}
