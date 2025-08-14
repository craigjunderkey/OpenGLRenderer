#pragma once
#include <vector>
#include "Path.h"

namespace Common
{
	class FileSystem
	{
	public:
		virtual std::vector<Path> getFilesInImmediateDirectory(Path directory) = 0;
		virtual std::vector<Path> getFilesInDirectory(Path directory) = 0;
		virtual std::vector<Path> getFilesInDirectory(Path directory, const char* extension) = 0;
		virtual bool fileExists(Path file) = 0;
		virtual ~FileSystem() = default;
	};
}
