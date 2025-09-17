#include <fstream>
#include <array>
#include <string>
#include "zip.h"
#include "json.hpp"
#include "PackageBuilder.h"
#include "types.h"
#include "ErrorReporter.h"
#include "Locator.h"

using namespace Resources;
using namespace Common;

using json = nlohmann::json;

PackageBuilder::PackageBuilder(const PreResourceFileMap& fileMap, const Path& outputDirectory)
	: fileMap_(fileMap), outputDirectory_(outputDirectory)
{
	// create staging directory path
	String stagingDirName = String::concatenate(outputDirectory.path().data(), STAGING_DIRECTORY);
	this->stagingDirectory_ = Path(stagingDirName.data());
	
	// create the directory itself
	Locator::fileSystem().createDirectory(this->stagingDirectory_);

	// create a subdirectory for each packable pre-resource module
	for (const PreResourceDescription& preResource : PreResourceMeta::getPreResources())
	{
		if (isPackable(preResource.type))
		{
			Path modulePath = Path::makeSubpath(this->stagingDirectory_, preResource.pkgModule);
			Locator::fileSystem().createDirectory(modulePath);
		}
	}
}

PackageBuilder::~PackageBuilder()
{
	Locator::fileSystem().destroyDirectory(this->stagingDirectory_);
}

void PackageBuilder::build(const Path& definition)
{
	// initialize with path's name
	PackageDefinition pkg = PackageDefinition(definition.name().data());
	
	// parse the package definition
	json jsonDef = json::parse(
		std::ifstream(definition.path().data())
	);

	// yoink the files
	for (const auto& jsonModule : jsonDef)
	{
		// get the current module
		std::string moduleName = static_cast<std::string>(jsonModule).data();
		const PreResourceDescription* preResource = PreResourceMeta::getPreResource(moduleName.data());
		
		// check that the module actually exists
		if (preResource == nullptr)
		{
			ErrorReporter::warn("Found non-existent module name " + moduleName + " in " + pkg.name + "; ignoring.");
			continue;
		}

		// check that the module corresponds with a packable pre-resource
		if (!isPackable(preResource->type))
		{
			ErrorReporter::warn("Tried to pack a " + std::string(preResource->name)
				+ " in " + pkg.name + ", but " + preResource->name + " is not packable; skipping.");
			continue;
		}

		// add each file in that module
		for (const auto& jsonPreResource : jsonModule)
		{
			std::string fileName = static_cast<std::string>(jsonPreResource).data();
			
			// attempt to get the path to raise any warnings
			this->fileMap_.getPath(preResource->type, fileName);
			
			pkg.addFile(preResource->type, std::move(fileName));
		}
	}

	build(pkg);
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

	build(pkg);
}

void PackageBuilder::build(const PackageDefinition& definition)
{

}