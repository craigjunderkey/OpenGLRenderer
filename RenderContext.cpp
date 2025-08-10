#include "RenderContext.h"
#include <numbers>
#include "VertexAttributes.h"
#include "VertexAttributeSets.h"
#include "Meshes.h"

using namespace Graphics;
using namespace AssetManagement;

RenderContext::RenderContext(Window& window, AssetManagement::ContentManager& contentManager, u32 virtualWidth, u32 virtualHeight)
	: window_(window),
	contentManager_(contentManager),
	virtualScreen_(createVirtualScreen(window, virtualWidth, virtualHeight))
{
	// enable depth testing
	glfwWindowHint(GL_DEPTH_BITS, 24);
	glEnable(GL_DEPTH_TEST);

	// enable blending -> transparent backgrounds
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

RenderContext::~RenderContext()
{
	for (RenderScene* scene : this->renderSequence_)
	{
		delete scene;
	}
}

RenderScene& RenderContext::getScene(u32 sceneIndex)
{
	return *this->renderSequence_.at(sceneIndex);
}

void RenderContext::addScene3D(u32 maxObjects)
{
	// calculate perspective projection
	f32 aspectRatio = (f32)this->window_.width() / (f32)this->window_.height();
	mat4 perspective = glm::perspective<f32>(std::numbers::pi / 2, aspectRatio, 0.1f, 1000.0f);

	// create 3d scene
	this->renderSequence_.push_back(new Scene3D(perspective, maxObjects));
}

void RenderContext::addSpriteBatch(const char* defaultEffect, u32 maxObjects)
{
	// calculate orthographic screen-space projection
	mat4 orthographic = glm::ortho<f32>(0.0f,
		this->virtualScreen_->width(),
		this->virtualScreen_->height(),
		0.0f, -1.0f, 1.0f);

	// create spritebatch
	this->renderSequence_.push_back(
		new SpriteBatch(contentManager_.spriteTextures(), contentManager_.fx(),
			std::string(defaultEffect), orthographic, maxObjects));
}

VirtualScreen* RenderContext::createVirtualScreen(Window& parentWindow, u32 virtualWidth, u32 virtualHeight)
{
	return new VirtualScreen(this->window_, virtualWidth, virtualHeight);
}

void RenderContext::render()
{
	this->virtualScreen_->begin();

	for (RenderScene* scene : this->renderSequence_)
	{
		render(scene);
	}

	this->virtualScreen_->end();

	glfwSwapBuffers(this->window_.id());
}

void RenderContext::render(RenderScene* scene)
{
	glClear(GL_DEPTH_BUFFER_BIT); // need we do anything about the color buffer?
	scene->render();
}

void RenderContext::initializeRenderer()
{
	VertexAttributes::initialize();
	VertexAttributeSets::initialize();
	Meshes::initialize();
}

void RenderContext::setBackgroundColor(Common::ColorRgba color)
{
	this->virtualScreen_->setBackgroundColor(color);
}