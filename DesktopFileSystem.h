#pragma once
#include "FileSystem.h"

namespace Common
{
	class DesktopFileSystem : public FileSystem
	{
	public:
		virtual std::vector<Path> getFilesInImmediateDirectory(const Path& directory) override;
		virtual std::vector<Path> getFilesInDirectory(const Path& directory) override;
		virtual std::vector<Path> getFilesInDirectory(const Path& directory, const char* extension) override;
		
		virtual bool fileExists(const Path& file) override;
	
		virtual void createDirectory(const Path& directory) override;
		virtual void destroyDirectory(const Path& directory) override;
	};
}
