#include "Scene3D.h"
#include "ErrorReporter.h"
#include "GlErrorChecker.h"

using namespace Graphics;
using namespace Common;

Scene3D::Scene3D(mat4& projectionTransform, size_t maxObjects)
	: program_(createShaderProgram()),
	maxObjects_(maxObjects)
{
	this->view_ = mat4(1.0f);
	this->program_.uniforms().set("p", projectionTransform);
	this->objects_.reserve(maxObjects_);
}

Scene3D::~Scene3D() {}

void Scene3D::draw(RenderObject&& object)
{
	if (this->objects_.size() >= this->maxObjects_)
		ErrorReporter::warn("Scene3D exceeded buffer size (" + std::to_string(maxObjects_) + "). Allocating more space!");

#pragma warning(suppress: 28020)
	this->objects_.push_back(std::move(object));
}

void Scene3D::draw(RenderObject object)
{
	if (this->objects_.size() >= this->maxObjects_)
		ErrorReporter::warn("Scene3D exceeded buffer size (" + std::to_string(maxObjects_) + "). Allocating more space!");
	
#pragma warning(suppress: 28020)
	this->objects_.push_back(std::move(object));
}

void Scene3D::setCameraPos(vec3 pos)
{
	this->view_ = glm::translate(glm::mat4(1.0), -pos);
}

void Scene3D::setView(mat4 viewTransform)
{
	this->view_ = std::move(viewTransform);
}

void Scene3D::setProjection(mat4& projectionTransform)
{
	this->program_.uniforms().set("p", projectionTransform);
}

void Scene3D::render()
{
	glEnable(GL_DEPTH_TEST);
	
	this->program_.use();
	
	for (int i = 0; i < this->objects_.size(); i++)
	{
		RenderObject& object = this->objects_[i];
		
		mat4 mv = this->view_ * object.transform;
		this->program_.uniforms().set("mv", mv);
		
		Mesh* mesh = object.mesh;
		mesh->bind();
		
		if (!mesh->hasEbo())
			glDrawArrays(GL_TRIANGLES, 0, mesh->count());
		else
			glDrawElements(GL_TRIANGLES, mesh->count(), GL_UNSIGNED_INT, 0);
	}

	this->objects_.clear();
}

ShaderProgram Scene3D::createShaderProgram()
{
	ShaderProgram program = ShaderProgram();

	Shader vertShader = Shader::fromFile("Shaders/vertex_shader.glsl", Shader::Type::Vertex);
	GlErrorChecker::checkShader(vertShader).report();

	Shader fragShader = Shader::fromFile("Shaders/fragment_shader.glsl", Shader::Type::Fragment);
	GlErrorChecker::checkShader(fragShader).report();

	program.attachShader(vertShader);
	program.attachShader(fragShader);
	program.link();
	GlErrorChecker::checkProgram(program).report();

	return program;
}