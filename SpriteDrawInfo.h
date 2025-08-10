#pragma once
#include "Types.h"
#include "UniformCommandBlock.h"
#include "Color.h"
#include "Rectangle.h"

namespace Graphics
{
	struct SpriteDrawInfo
	{
		friend class SpriteBatch;

	public:
		Common::Rectangle region = Common::Rectangle();
		vec2 scale = vec2(1, 1);
		f32 angle = 0;
		vec2 pivotPoint = vec2(0, 0);
		Common::ColorRgb tint = Common::ColorRgb(0xFF, 0xFF, 0xFF);

	private:
		u8 flags = 0x0;
		const char* effect = nullptr;
		UniformCommandBlock* effectUniforms = nullptr;

	public:
		enum class Flag
		{
			FlipH = 0x01,
			FlipV = 0x02
		};

		SpriteDrawInfo& setFlag(Flag flag)
		{
			this->flags |= (u8)flag;
			return *this;
		}

		SpriteDrawInfo& clearFlag(Flag flag)
		{
			this->flags &= ~(u8)flag;
			return *this;
		}

		SpriteDrawInfo& setEffect(const char* effectName)
		{
			this->effect = effectName;
			return *this;
		}

		template <typename T>
		SpriteDrawInfo& scheduleUniformSet(std::string uniform, T value)
		{
			Common::ErrorReporter::panicElse(this->effect != nullptr,
				"Scheduled an assignment of uniform \"" + uniform + "\" but did not assign an effect.");

			if (this->effectUniforms == nullptr)
				this->effectUniforms = new UniformCommandBlock();

			this->effectUniforms->addCommand(new UniformSet<T>(uniform, value));
			return *this;
		}

		SpriteDrawInfo& setRegion(Common::Rectangle region)
		{
			this->region = region;
			return *this;
		}

		SpriteDrawInfo& setScale(vec2 scale)
		{
			this->scale = scale;
			return *this;
		}

		SpriteDrawInfo& setAngle(f32 radians)
		{
			this->angle = radians;
			return *this;
		}

		SpriteDrawInfo& setPivot(vec2 pivotPoint)
		{
			this->pivotPoint = pivotPoint;
			return *this;
		}

		SpriteDrawInfo& setTint(Common::ColorRgb color)
		{
			this->tint = color;
			return *this;
		}
	};
}