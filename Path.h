#pragma once
#include <cstring>
#include <iostream>
#include "Types.h"
#include "String.h"

namespace Common
{
	class Path
	{
	public:
		Path(const char* path);
		~Path();
		
		const char* path() const { return this->path_; }
		
		String name();
		Path parentDirectory();
		bool hasParentDirectory();
		String extension();
		bool hasExtension();
		bool extensionMatches(const char* extension);
		String fullExtension();

	private:
		const char* findFirst(char toFind) const;
		const char* findLast(char toFind) const;
		bool contains(char toFind) const;
		String substring(i32 start, i32 size) const;
		String substring(const char* start, i32 size) const;

		const char* path_;
	};

	inline std::ostream& operator<<(std::ostream& os, const Path& path)
	{
		os << path.path();
		return os;
	}
}
