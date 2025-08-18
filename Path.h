#pragma once
#include <cstring>
#include <iostream>
#include <optional>
#include "Types.h"
#include "String.h"

namespace Common
{
	struct PathPattern;
	
	class Path
	{
	public:
		Path(const char* path);
		Path();
		
		Path(Path&& other) noexcept;
		Path& operator=(Path&& other) noexcept;
		static Path makePreformatted(String&& path);

		const String& path() const { return this->path_; }
		
		String name() const;
		Path parentDirectory() const;
		bool hasParentDirectory() const;
		String extension() const;
		bool hasExtension() const;
		bool extensionMatches(const char* extension) const;
		String fullExtension() const;
		bool fullExtensionMatches(const char* fullExtension) const;

		bool isPattern() const;
		PathPattern makePattern() const;
	
	private:
		String path_;

		Path(String&& path);
		String makeFormattedPath(const char* path);
	};

	inline std::ostream& operator<<(std::ostream& os, const Path& path)
	{
		os << path.path();
		return os;
	}
}
