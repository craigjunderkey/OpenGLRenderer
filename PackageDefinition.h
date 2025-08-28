#pragma once
#include "Resource.h"
#include "Path.h"

namespace Resources
{
	class PackageDefinition : public Resource
	{
	public:
		PackageDefinition(String archiveFileName)
			: archiveFileName_(std::move(archiveFileName)),
			isLoaded_(false)
		{}
		
		const String& archiveFileName() const { return this->archiveFileName_; }
		void initResource() override {}
		
	private:
		String archiveFileName_;
		bool isLoaded_;
	};
}
