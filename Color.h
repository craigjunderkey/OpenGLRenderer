#pragma once
#include "Types.h"

namespace Common
{
	// It's kind of terrible that ColorRgb uses u8s as its representation
	// while ColorRgba uses f32s despite sharing a naming convention.

	struct ColorRgba
	{
		ColorRgba(f32 r, f32 g, f32 b) : r(r), g(g), b(b) {}
		ColorRgba(f32 r, f32 g, f32 b, f32 a) : r(r), g(g), b(b), a(a) {}
		ColorRgba(f32 luminance) : r(luminance), g(luminance), b(luminance) {}
		ColorRgba() {}

		f32 r = 0.0f;
		f32 g = 0.0f;
		f32 b = 0.0f;
		f32 a = 1.0f;
	};

	struct ColorRgb
	{
		ColorRgb() {}
		ColorRgb(u8 r, u8 g, u8 b) : r(r), g(g), b(b) {}
		ColorRgb(u8 luminance) : r(luminance), g(luminance), b(luminance) {}

		u8 r = 0;
		u8 g = 0;
		u8 b = 0;
	};
}
