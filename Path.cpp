#include "Path.h"

using namespace Common;

Path::Path(const char* path)
{
	u32 length = strlen(path);
	char* formattedPath = new char[length + 1];
	memcpy(formattedPath, path, length + 1);

	for (int i = 0; i < length; i++)
	{
		if (path[i] == '\\')
		{
			formattedPath[i] = '/';
		}
	}

	this->path_ = formattedPath;
}

Path::~Path()
{
	delete this->path_;
}

String Path::name()
{
	const char* nameStart = findFirst('/');
	const char* nameEnd = findLast('.');

	if (nameStart == nullptr)
		nameStart = this->path_;
	else
		nameStart++; // move past /

	if (nameEnd == nullptr)
		nameEnd = this->path_ + strlen(this->path_);

	i32 size = nameEnd - nameStart;
	return substring(nameStart, size);
}

Path Path::parentDirectory()
{
	const char* dir = findLast('/');

	assert(dir != nullptr);

	i32 size = dir - this->path_;
	return Path(substring(0, size).text);
}

bool Path::hasParentDirectory()
{
	return this->contains('/');
}

String Path::extension()
{
	const char* start = findLast('.');

	assert(start != nullptr);
	
	start++; // move past .

	const char* end = this->path_ + strlen(this->path_);
	i32 size = end - start;
	return substring(start, size);
}

bool Path::hasExtension()
{
	return this->contains('.');
}

String Path::fullExtension()
{
	const char* start = findFirst('.');

	assert(start != nullptr);

	start++; // move past .

	const char* end = this->path_ + strlen(this->path_);
	i32 size = end - start;
	return substring(start, size);
}

const char* Path::findFirst(char toFind) const
{
	const char* current = this->path_;

	while (*current != '\0')
	{
		if (*current == toFind)
		{
			return current;
		}
		else
		{
			current++;
		}
	}

	return nullptr;
}

const char* Path::findLast(char toFind) const
{
	const char* current = this->path_ + strlen(this->path_);
	const char* start = this->path_;

	while (current != start)
	{
		if (*current == toFind)
		{
			return current;
		}
		else
		{
			current--;
		}
	}

	return nullptr;
}

bool Path::contains(char toFind) const
{
	return findFirst(toFind) != nullptr;
}

String Path::substring(i32 start, i32 size) const
{
	return String(this->path_ + start, size);
}

String Path::substring(const char* start, i32 size) const
{
	return String(start, size);
}
