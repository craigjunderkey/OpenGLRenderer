#pragma once
#include "FileSystem.h"

namespace Common
{
	class DesktopFileSystem : public FileSystem
	{
	public:
		virtual std::vector<Path> getFilesInImmediateDirectory(Path directory) override;
		virtual std::vector<Path> getFilesInDirectory(Path directory) override;
		virtual std::vector<Path> getFilesInDirectory(Path directory, const char* extension) override;
		virtual bool fileExists(Path file) override;
	};
}
