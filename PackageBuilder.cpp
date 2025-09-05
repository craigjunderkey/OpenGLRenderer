#include "PackageBuilder.h"

using namespace Resources;
using namespace Common;

PackageBuilder::PackageBuilder(const PreResourceFileMap& fileMap, const Path& outputDirectory)
	: fileMap_(fileMap), outputDirectory_(outputDirectory)
{
}

void PackageBuilder::build(const Path& definition)
{

}

void PackageBuilder::buildUniversal()
{
	PackageDefinition pkg = PackageDefinition("all");

	for (const PreResourceDescription& preResource : PreResourceMeta::getPreResources())
	{
		if (!isPackable(preResource.type))
			continue;

		const std::unordered_map<std::string, Path>& map = fileMap_.getMap(preResource.type);

		for (const auto& file : map)
		{
			std::string name = file.second.name().data();
			pkg.addFile(preResource.type, std::move(name));
		}
	}
}

void PackageBuilder::build(const PackageDefinition& definition)
{

}