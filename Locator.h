#pragma once
#include "FileSystem.h"
#include "DesktopFileSystem.h"

namespace Common
{
	class Locator
	{
	public:
		static void initialize()
		{
			fileSystem_ = new DesktopFileSystem();
		}

		static FileSystem& fileSystem() { return *fileSystem_; }

	private:
		static FileSystem* fileSystem_;
	};
}