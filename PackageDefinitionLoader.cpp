#include "PackageDefinitionLoader.h"
#include "PackageDefinition.h"

using namespace Resources;
using namespace Common;

Resource* PackageDefinitionLoader::load(const Path& source) const
{
	String name = source.name();
	String pathDesc = name + ".zip";
	return new PackageDefinition(std::move(pathDesc));
}

std::unique_ptr<ResourceLoader> PackageDefinitionLoader::newInstance() const
{
	return std::make_unique<PackageDefinitionLoader>();
}