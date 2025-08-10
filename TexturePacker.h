#pragma once
#include <vector>
#include <string>
#include "Texture.h"
#include "TextureAtlas.h"
#include "Image.h"
#include "Rectangle.h"
#include "Types.h"

namespace AssetManagement
{
	class TexturePacker
	{
	public:
		static TextureAtlas pack(const std::vector<std::string>& filePaths, Graphics::Texture::Unit unit, const std::string& name, bool exportOnCompletion);
	
	private:
		static const u32 INTERVAL = 64;
		
		struct TexData
		{
			TexData() {}
			TexData(Common::Image&& image, std::string name) : image(std::move(image)), name(name) {}

			Common::Image image;
			std::string name;
		};

		struct TexRect
		{
			TexRect() {}
			TexRect(Common::Rectangle rect, u32 id) : rect(rect), id(id) {}

			Common::Rectangle rect;
			u32 id;
		};

		static std::string getPathName(const std::string& path);
		static bool compareRects(TexRect& a, TexRect& b);
		static u32 calculateStartingAtlasSize(const std::vector<TexRect>& rects);
		static bool packRects(std::vector<TexRect>& rects, u32 size);
		static u32 packRectsUndershootCase(std::vector<TexRect>& rects, u32 size);
		static u32 packRectsOvershootCase(std::vector<TexRect>& rects, u32 size);
		static TextureAtlas createAtlas(Graphics::Texture&& texture, const std::vector<TexData>& data, const std::vector<TexRect>& rects);
		static void exportAtlas(const std::string& name, const Common::Image& atlasImage, const std::vector<TexData>& data, const std::vector<TexRect>& rects);
	};
}
