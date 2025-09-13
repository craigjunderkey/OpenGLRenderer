#pragma once
#include "Path.h"
#include "PreResourceFileMap.h"
#include "PackageDefinition.h"

namespace Resources
{
	class PackageBuilder
	{
	public:
		PackageBuilder(const PreResourceFileMap& fileMap, const Common::Path& outputDirectory);
		~PackageBuilder();
		void build(const Common::Path& definition);
		void buildUniversal();
	
	private:
		void build(const PackageDefinition& definition);

		const PreResourceFileMap& fileMap_;
		const Common::Path& outputDirectory_;
		Common::Path stagingDirectory_;

		const char* STAGING_DIRECTORY = "StagingArea";
	};
}
