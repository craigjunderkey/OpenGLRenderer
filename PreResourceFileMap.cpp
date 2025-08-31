#include <vector>
#include "PreResourceFileMap.h"
#include "FileManager.h"
#include "String.h"
#include "ErrorReporter.h"

using namespace Resources;
using namespace Common;
using namespace AssetManagement;

PreResourceFileMap::PreResourceFileMap()
{
	for (i32 i = 0; i < PreResourceMeta::NUM_PRE_RESOURCES; i++)
	{
		fillMap(i, PreResourceMeta::getPreResources()[i]);
	}
}

void PreResourceFileMap::fillMap(i32 index, const PreResourceDescription& preResource)
{
	// get the destination map
	std::unordered_map<std::string, Path>& destination = this->modules_[index];
	
	// get every path we plan to add
	std::vector<Path> paths = std::move(FileManager::getAllFilesFromModule(preResource.pkgModule));
	destination.reserve(paths.size());

	// move each Path and its name to the destination map
	for (Path& path : paths)
	{
		String name = path.name();
		std::string stdName = std::string(name.data()); // shameful string duplication
		destination.insert({ std::move(stdName), std::move(path) });
	}
}

const std::unordered_map<std::string, Path>& PreResourceFileMap::getMap(PreResourceType type) const
{
	return this->modules_[(u32)type];
}

const Path& PreResourceFileMap::getPath(PreResourceType type, const std::string& name) const
{
	const std::unordered_map<std::string, Path>& map = this->modules_[(u32)type];
	auto it = map.find(name);

	if (it != map.end())
	{
		return (*it).second;
	}
	else
	{
		const char* preResourceType = PreResourceMeta::getPreResource(type)->name;
		ErrorReporter::panic("Could not find " + name + " named " + name + ".");
	}
}