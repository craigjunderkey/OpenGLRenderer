#pragma once
#include "Path.h"
#include "PreResourceFileMap.h"

namespace Resources
{
	class PackageBuilder
	{
	public:
		PackageBuilder(const PreResourceFileMap& fileMap);
		void build(const Common::Path& source, const Common::Path& destination);
		void buildUniversalPackage(const Common::Path& destination);
	
	private:
		const PreResourceFileMap& fileMap_;
	};
}
