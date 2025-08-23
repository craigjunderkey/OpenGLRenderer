#pragma warning( disable : 6011 )

#include "ShaderEffect.h"
#include "ErrorReporter.h"
#include "GlErrorChecker.h"

using namespace Graphics;
using namespace AssetManagement;
using namespace Common;

ShaderEffect::ShaderEffect(ShaderIdBlock shaders)
	: shaders_(shaders), program_(ShaderProgram())
{
}

void ShaderEffect::link(ShaderPtrBlock* pointers)
{
	if (pointers->compute != nullptr)
	{
		linkStandardEffect(pointers);
	}
	else
	{
		linkComputeEffect(pointers);
	}
}

void ShaderEffect::linkStandardEffect(ShaderPtrBlock* ptrs)
{
	// vertex
	ErrorReporter::panicElse(ptrs->vertex, "Shader effect requires a vertex shader.");
	this->program_.attachShader(*ptrs->vertex);

	// tessellation
	if (ptrs->tessControl || ptrs->tessEval)
	{
		ErrorReporter::panicElse(!ptrs->tessControl || !ptrs->tessEval,
			"Shader effect has one tessellation stage but not both.");

		this->program_.attachShader(*ptrs->tessControl);
		this->program_.attachShader(*ptrs->tessEval);
	}

	// geometry
	if (ptrs->geometry)
		this->program_.attachShader(*ptrs->geometry);

	// fragment
	if (ptrs->fragment)
		this->program_.attachShader(*ptrs->fragment);
}

void ShaderEffect::linkComputeEffect(ShaderPtrBlock* ptrs)
{
	this->program_.attachShader(*ptrs->compute);
}

void ShaderEffect::initResource()
{
	this->program_.link();
	GlErrorChecker::checkProgram(this->program_).report();
}

UniformManager& ShaderEffect::uniforms()
{
	return this->program_.uniforms();
}