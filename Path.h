#pragma once
#include <cstring>
#include <iostream>
#include <optional>
#include "Types.h"
#include "String.h"

namespace Common
{
	class Path
	{
	public:
		Path(const char* path);
		
		const String& path() const { return this->path_; }
		
		String name() const;
		Path parentDirectory() const;
		bool hasParentDirectory() const;
		String extension() const;
		bool hasExtension() const;
		bool extensionMatches(const char* extension) const;
		String fullExtension() const;

		bool isPattern() const;
		PathPattern getPattern() const;
	
	private:
		String path_;

		Path(String&& path);
		String makeFormattedPath(const char* path);
	};

	struct PathPattern
	{
		PathPattern(Path&& directory, std::optional<String>&& extension)
			: directory(std::move(directory)), extension(std::move(extension)) {
		}

		Path directory;
		std::optional<String> extension;
	};

	inline std::ostream& operator<<(std::ostream& os, const Path& path)
	{
		os << path.path();
		return os;
	}
}
