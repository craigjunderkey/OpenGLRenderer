#pragma once
#include "Resource.h"
#include "Path.h"

namespace Resources
{
	class PackageDefinition : public Resource
	{
	public:
		PackageDefinition(const char* archivePath)
			: archivePath_(Common::Path(archivePath)),
			isLoaded_(false)
		{}
		
		const Common::Path& archivePath() const { return this->archivePath_; }
		void initResource() override {}
		
	private:
		Common::Path archivePath_;
		bool isLoaded_;
	};
}
