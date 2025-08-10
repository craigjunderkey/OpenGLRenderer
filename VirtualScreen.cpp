#include "VirtualScreen.h"
#include "VertexAttributeSets.h"
#include "GlErrorChecker.h"
#include "ErrorReporter.h"
#include "Texture2D.h"
#include "Rectangle.h"
#include "GlImageFormat.h"

using namespace Graphics;
using namespace Common;

VirtualScreen::VirtualScreen(const Window& parentWindow, u32 width, u32 height)
	: parentWindow_(parentWindow),
	width_(width),
	height_(height),
	fbo_(FrameBufferObject()),
	colorAttachment_(Texture(nullptr, width, height, GlImageFormat::Rgba, Texture::Unit::Attachment)),
	depthStencilAttachment_(RenderBufferObject(GlImageFormat::Depth24Stencil8, width, height)),
	screenQuad_(createScreenQuad()),
	shaderProgram_(createShaderProgram(Texture::Unit::Attachment)),
	backgroundColor_(ColorRgba(1.0f))
{
	fbo_.attach(colorAttachment_, FrameBufferObject::AttachmentType::Color);
	fbo_.attach(depthStencilAttachment_, FrameBufferObject::AttachmentType::DepthStencil);
	ErrorReporter::panicElse(fbo_.isComplete(), "FBO in VirtualScreen is not complete.");
}

VirtualScreen::~VirtualScreen()
{
}

void VirtualScreen::begin()
{
	glViewport(0, 0, this->width_, this->height_);
	this->fbo_.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void VirtualScreen::end()
{
	// prepare window to be drawn to
	glViewport(0, 0, parentWindow_.width(), parentWindow_.height());
	this->fbo_.unbind();
	glClearColor(backgroundColor_.r, backgroundColor_.g, backgroundColor_.b, backgroundColor_.a);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw our FBO's color attachment to a screen-sized quad
	this->shaderProgram_.use();
	this->screenQuad_.bind();
	this->colorAttachment_.bind();
	glDisable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, this->screenQuad_.count(), GL_UNSIGNED_INT, 0);
}

void VirtualScreen::setBackgroundColor(ColorRgba color)
{
	this->backgroundColor_ = color;
}

Mesh VirtualScreen::createScreenQuad()
{
	f32 vertices[] = {
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		-1.0f, 1.0f,	0.0f, 1.0f
	};

	u32 indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	
	return Mesh(vertices, sizeof(vertices), indices, 6, *VertexAttributeSets::POSITION2D_UV);
}

ShaderProgram VirtualScreen::createShaderProgram(Texture::Unit textureUnit)
{
	ShaderProgram program = ShaderProgram();

	Shader vertex = Shader::fromFile("Shaders/virtual_screen_vert.glsl", Shader::Type::Vertex);
	GlErrorChecker::checkShader(vertex);

	Shader fragment = Shader::fromFile("Shaders/virtual_screen_frag.glsl", Shader::Type::Fragment);
	GlErrorChecker::checkShader(fragment);

	program.attachShader(vertex);
	program.attachShader(fragment);
	program.link();
	GlErrorChecker::checkProgram(program);

	this->shaderProgram_.uniforms().set("screenTexture", textureUnit);

	return program;
}
