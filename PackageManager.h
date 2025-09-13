#pragma once
#include "StringId.h"
#include "StringIdTable.h"
#include "PackageManifest.h"

namespace Resources
{
	class PackageManager
	{
	public:
		PackageManager() = delete;

		static void setPackageDirectory(const char* directory);
		static void buildAllPackages();
		static void loadAllManifests();
		static void load(StringId package);
		static void unload(StringId package);

	private:
		static Common::StringIdTable<PackageManifest> manifests_;
		static Common::Path pkgDir_;
	};
}