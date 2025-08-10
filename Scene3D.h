#pragma once
#include <vector>
#include "Types.h"
#include "RenderObject.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "RenderScene.h"

namespace Graphics
{
	class Scene3D : public RenderScene
	{
	public:
		static constexpr size_t DEFAULT_MAX_OBJECTS = 256;

		Scene3D(mat4& projectionTransform, size_t maxObjects);
		~Scene3D();
		void draw(RenderObject&& object);
		void draw(RenderObject object);
		void setCameraPos(vec3 pos); // TODO: get rid of this
		
		void render() override;
		void setView(mat4 viewTransform) override;
		void setProjection(mat4& projectionTransform) override;
	
	private:
		mat4 view_;
		std::vector<RenderObject> objects_;
		ShaderProgram program_;
		size_t maxObjects_;

		ShaderProgram createShaderProgram();
	};
}
