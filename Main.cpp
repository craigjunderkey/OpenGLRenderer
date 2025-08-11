#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <numbers>
#include "Window.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "GlErrorChecker.h"
#include "Types.h"
#include "Mesh.h"
#include "VertexAttributeSets.h"
#include "VertexAttributes.h"
#include "Meshes.h"
#include "RenderObject.h"
#include "Scene3D.h"
#include "SpriteBatch.h"
#include "VirtualScreen.h"
#include "RenderContext.h"
#include "ContentManager.h"
#include "UniformCommandBlock.h"

using namespace Graphics;
using namespace Common;
using namespace AssetManagement;

void drawWorld(Scene3D& scene, RenderObject& buddy, RenderObject& champ, f64 time)
{
	buddy.transform =
		glm::rotate(mat4(1.0f), glm::radians(-0.4f), vec3(1.0f, 0.0f, 0.0f)) * buddy.transform;
	buddy.transform =
		glm::rotate(mat4(1.0f), glm::radians(0.2f), vec3(0.0f, 0.0f, 1.0f)) * buddy.transform;
	
	scene.setCameraPos(vec3(0.0f, 0.0f, 0.1f + time * 0.1f));
	scene.draw(buddy);
	scene.draw(champ);
}

int main()
{
	// create window
	Window window(800, 600, "Joyous is he who murders and eats people.");
	RenderContext::initializeRenderer();

	// load content
	ContentManager contentManager = ContentManager(true);
	contentManager.fx().getEffect("spritebatch_flash").uniforms().set("speed", 2.0f);

	// create render context
	RenderContext renderContext = RenderContext(window, contentManager, 800, 600);
	renderContext.setScreenEffect("virtual_screen");
	
	renderContext.addScene3D();
	Scene3D& scene3D = (Scene3D&)renderContext.getScene(0);
	
	renderContext.addSpriteBatch();
	SpriteBatch& spriteBatch = (SpriteBatch&)renderContext.getScene(1);
	spriteBatch.setZoomLevel(4);

	// create 3d quads
	RenderObject buddy = RenderObject(Meshes::TRIANGLE);
	RenderObject champ = RenderObject(Meshes::QUAD);
	champ.transform = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, -2.0f)) * champ.transform;

	while (!glfwWindowShouldClose(window.id()))
	{
		drawWorld(scene3D, buddy, champ, glfwGetTime());

		spriteBatch.draw("burble", vec2(0, 0));
		
		spriteBatch.draw("grungle", vec2(24, 0),
			SpriteDrawInfo().setTint(ColorRgb(0xFF, 0, 0))
		);
		
		SpriteDrawInfo info;
		info.setTint(ColorRgb(0, 0, 0xFF))
			.setFlag(SpriteDrawInfo::Flag::FlipH)
			.setFlag(SpriteDrawInfo::Flag::FlipV);
		spriteBatch.draw("babyman", vec2(96, 96), info);
		
		spriteBatch.draw("pantfreak", vec2(70, 100));

		info = SpriteDrawInfo();
		info.setEffect("spritebatch_flash")
			.scheduleUniformSet("time", (f32)glfwGetTime() + 1.57f)
			.setTint(ColorRgb(0xFF, 0, 0))
			.setFlag(SpriteDrawInfo::Flag::FlipH);
		spriteBatch.draw("tallbaby", vec2(120, 64), info);

		info = SpriteDrawInfo();
		info.setEffect("spritebatch_flash")
			.scheduleUniformSet("time", (f32)glfwGetTime() + 0.78f)
			.setTint(ColorRgb(0, 0xFF, 0))
			.setFlag(SpriteDrawInfo::Flag::FlipH);
		spriteBatch.draw("tallbaby", vec2(144, 64), info);

		info = SpriteDrawInfo();
		info.setEffect("spritebatch_flash")
			.scheduleUniformSet("time", (f32)glfwGetTime())
			.setTint(ColorRgb(0, 0, 0xFF))
			.setFlag(SpriteDrawInfo::Flag::FlipH);
		spriteBatch.draw("tallbaby", vec2(168, 64), info);

		renderContext.render();

		glfwPollEvents();
	}
}