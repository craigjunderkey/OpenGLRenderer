#pragma once
#include "Types.h"

namespace Graphics
{
	class RenderScene
	{
	public:
		virtual void render() = 0;
		virtual void setView(mat4 viewTransform) = 0;
		virtual void setProjection(mat4& projectionTransform) = 0;
		virtual ~RenderScene() {};
	};
}
