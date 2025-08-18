#pragma once
#include <vector>
#include "Texture.h"
#include "TextureAtlas.h"
#include "Image.h"
#include "Rectangle.h"
#include "Types.h"
#include "Path.h"
#include "String.h"

namespace AssetManagement
{
	class TexturePacker
	{
	public:
		static TextureAtlas pack(const std::vector<Common::Path>& filePaths, Graphics::Texture::Unit unit, const char* name, bool exportOnCompletion);
	
	private:
		static const u32 INTERVAL = 128;
		
		struct TexData
		{
			TexData() : name(String::makeEmpty()) {}
			TexData(Common::Image&& image, String&& name) : image(std::move(image)),
				name(std::move(name)) {}

			Common::Image image;
			String name;
		};

		struct TexRect
		{
			TexRect() : id(0) {}
			TexRect(Common::Rectangle rect, u32 id) : rect(rect), id(id) {}

			Common::Rectangle rect;
			u32 id;
		};

		static bool compareRects(TexRect& a, TexRect& b);
		static u32 calculateStartingAtlasSize(const std::vector<TexRect>& rects);
		static bool packRects(std::vector<TexRect>& rects, u32 size);
		static u32 packRectsUndershootCase(std::vector<TexRect>& rects, u32 size);
		static u32 packRectsOvershootCase(std::vector<TexRect>& rects, u32 size);
		static TextureAtlas createAtlas(Graphics::Texture&& texture, const std::vector<TexData>& data, const std::vector<TexRect>& rects);
		static void exportAtlas(const char* name, const Common::Image& atlasImage, const std::vector<TexData>& data, const std::vector<TexRect>& rects);
	};
}
