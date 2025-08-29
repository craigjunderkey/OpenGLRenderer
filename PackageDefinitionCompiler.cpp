#include "PackageDefinitionCompiler.h"

using namespace Resources;
using namespace Common;

void PackageDefinitionCompiler::compile(const Path& source, const Path& destination) const
{

}

std::unique_ptr<ResourceCompiler> PackageDefinitionCompiler::newInstance() const
{
	return std::make_unique<PackageDefinitionCompiler>();
}