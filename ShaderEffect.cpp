#include "ShaderEffect.h"
#include "ErrorReporter.h"
#include "GlErrorChecker.h"

using namespace Graphics;
using namespace AssetManagement;
using namespace Common;

// TODO: postpone construction of the ShaderProgram to initResource;
//		 take StringIds for effect info

ShaderEffect::ShaderEffect(const ShaderCache& cache, i32 vertex, i32 geometry, i32 fragment, i32 tessControl, i32 tessEval)
{
	// vertex
	ErrorReporter::panicElse(vertex != ShaderCache::NO_SHADER, "Shader effect requires a vertex shader.");
	this->program_.attachShader(cache.getShader(vertex));

	// tessellation
	if (tessControl != ShaderCache::NO_SHADER || tessEval != ShaderCache::NO_SHADER)
	{
		ErrorReporter::panicElse(tessControl == ShaderCache::NO_SHADER
			|| tessEval == ShaderCache::NO_SHADER,
			"Shader effect has one tesselation stage but not both.");
		
		this->program_.attachShader(cache.getShader(tessControl));
		this->program_.attachShader(cache.getShader(tessEval));
	}

	// geometry
	if (geometry != ShaderCache::NO_SHADER)
		this->program_.attachShader(cache.getShader(geometry));

	// fragment shader
	if (fragment != ShaderCache::NO_SHADER)
		this->program_.attachShader(cache.getShader(fragment));

	// link and report
	this->program_.link();
	GlErrorChecker::checkProgram(this->program_).report();
}

ShaderEffect::ShaderEffect(const ShaderCache& cache, i32 compute)
{
	assert(compute != ShaderCache::NO_SHADER); // if this gets through, then it's my fault
	this->program_.attachShader(cache.getShader(compute));
	this->program_.link();
	GlErrorChecker::checkProgram(this->program_).report();
}

UniformManager& ShaderEffect::uniforms()
{
	return this->program_.uniforms();
}