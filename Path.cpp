#include "Path.h"
#include "PathPattern.h"

using namespace Common;

Path::Path(const char* path)
	: path_(makeFormattedPath(path))
{
}

Path::Path(String&& path)
	: path_(std::move(path))
{
}

Path::Path()
	: path_(String::makeEmpty())
{
}

Path::Path(Path&& other) noexcept
	: path_(std::move(other.path_))
{
}

Path Path::makePreformatted(String&& path)
{
	return Path(std::move(path));
}

Path& Path::operator=(Path&& other) noexcept
{
	if (this != &other)
	{
		this->path_ = std::move(other.path_);
	}

	return *this;
}

String Path::makeFormattedPath(const char* path)
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

	return String::makeOwner(formattedPath);
}

String Path::name() const
{
	const char* nameStart = path_.findLast('/');
	const char* nameEnd = path_.findLast('.');

	if (nameStart == nullptr)
		nameStart = path_.data();
	else
		nameStart++; // move past /

	if (nameEnd == nullptr)
		nameEnd = path_.data() + path_.length();

	i32 size = nameEnd - nameStart;
	
	return path_.makeSubstringFromAddress(nameStart, size);
}

Path Path::parentDirectory() const
{
	const char* dir = path_.findLast('/');

	assert(dir != nullptr);

	i32 size = dir - path_.data();
	return Path(path_.makeSubstring(0, size));
}

bool Path::hasParentDirectory() const
{
	return path_.contains('/');
}

String Path::extension() const
{
	const char* start = path_.findLast('.');

	assert(start != nullptr);
	
	start++; // move past .

	const char* end = this->path_.data() + this->path_.length();
	i32 size = end - start;
	return path_.makeSubstringFromAddress(start, size);
}

bool Path::hasExtension() const
{
	return path_.contains('.');
}

bool Path::extensionMatches(const char* extension) const
{
	const char* start = path_.findLast('.');
	
	bool hasExtension = start != nullptr;
	if (!hasExtension)
		return false;

	start++;
	return strcmp(start, extension) == 0;
}

String Path::fullExtension() const
{
	const char* start = path_.findFirst('.');

	assert(start != nullptr);

	start++; // move past .

	const char* end = path_.data() + path_.length();
	i32 size = end - start;
	return path_.makeSubstringFromAddress(start, size);
}

bool Path::fullExtensionMatches(const char* fullExtension) const
{
	const char* start = path_.findFirst('.');
	
	bool hasExtension = start != nullptr;
	if (!hasExtension)
		return false;
	
	start++;
	return strcmp(start, fullExtension) == 0;
}

bool Path::isPattern() const
{
	return path_.contains('*');
}

PathPattern Path::makePattern() const
{
	assert(this->isPattern(), "Tried to get pattern but this is not a pattern.");
	assert(this->hasParentDirectory(), "Patterns must start with a directory.");
	assert(path_[path_.findLastIndex('*') - 1] == '/', "Patterns must immediately follow a /.");

	Path directory = this->parentDirectory();
	
	std::optional<String> extension;
	if (this->hasExtension())
	{
		extension.emplace(this->fullExtension());
	}

	return PathPattern(std::move(directory), std::move(extension));
}