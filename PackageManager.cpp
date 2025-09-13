#include "PackageManager.h"
#include "PreResourceFileMap.h"
#include "PreResourceMeta.h"
#include "PackageBuilder.h"

using namespace Resources;
using namespace Common;

void PackageManager::setPackageDirectory(const char* directory)
{
	pkgDir_ = Path(directory);
}

void PackageManager::buildAllPackages()
{
	// get every pre-resource we found
	PreResourceFileMap fileMap = PreResourceFileMap();

	// construct a builder and retrieve all the definitions
	PackageBuilder builder = PackageBuilder(fileMap, pkgDir_);
	const auto& definitions = fileMap.getMap(PreResourceType::PackageDefinition);

	// optionally build the universal package
	builder.buildUniversal();

	// build each other package
	for (const auto& definition : definitions)
	{
		builder.build(definition.second);
	}
}