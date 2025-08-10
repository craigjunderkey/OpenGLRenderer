#include "GlResult.h"
#include <cstdlib>
#include <cassert>
#include "ErrorReporter.h"

using namespace Graphics;

void GlResult::print()
{
	if (this->log_ != nullptr)
		Common::ErrorReporter::report(this->log_);
}

void GlResult::report()
{
	if (!isOk())
	{
		print();
		exit(EXIT_FAILURE);
	}
}

GlResult::GlResult(bool isOk) : isOk_(isOk) {}

GlResult::~GlResult()
{
	if (this->log_ != nullptr)
		free(log_);
}

GlResult GlResult::makeSuccess()
{
	return GlResult(true);
}

GlResult GlResult::makeFailure()
{
	return GlResult(false);
}

GlResult GlResult::makeFailure(char* log)
{
	GlResult result = GlResult(false);
	result.log_ = log;
	return result;
}