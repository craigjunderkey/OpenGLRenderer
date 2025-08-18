#include <iostream>
#include <fstream>
#include <algorithm>
#include "json.hpp"
#include "TexturePacker.h"
#include "Image.h"
#include "ImageBuilder.h"
#include "ImageWriter.h"
#include "FileManager.h"

using json = nlohmann::json;

using namespace AssetManagement;
using namespace Graphics;
using namespace Common;

bool TexturePacker::compareRects(TexRect& a, TexRect& b)
{
	return a.rect.size.y > b.rect.size.y;
}

TextureAtlas TexturePacker::pack(const std::vector<Path>& filePaths, Texture::Unit unit, const char* name, bool exportOnCompletion)
{
	// load all the images
	u32 texCount = filePaths.size();
	std::vector<TexData> data;
	std::vector<TexRect> rects;
	data.reserve(texCount);
	rects.reserve(texCount);
	
	for (const Path& path : filePaths)
	{
		Image texImage = Image(path.path().data(), Image::Format::Rgba, false);
		rects.push_back(TexRect(Rectangle(texImage.width, texImage.height), rects.size()));
		data.push_back(TexData(std::move(texImage), std::move(path.name())));
	}

	// sort rects by height
	std::sort(rects.begin(), rects.end(), compareRects);

	// calculate starting atlas size
	u32 size = calculateStartingAtlasSize(rects);

	// pack the rectangles
	bool packedSuccessfully = packRects(rects, size);

	if (packedSuccessfully)
		size = packRectsOvershootCase(rects, size);
	else
		size = packRectsUndershootCase(rects, size);

	std::cout << "Packed " << name << " (" << texCount << " textures, " << size << "px).\n";

	// generate atlas image
	ImageBuilder builder = ImageBuilder(size, size, Image::Format::Rgba);
	for (const TexRect& rect : rects)
	{
		builder.writeRegion(rect.rect, data[rect.id].image.data);
	}
	Image atlasImage = builder.build();

	// write texture atlas data to disk
	if (exportOnCompletion)
		exportAtlas(name, atlasImage, data, rects);

	// create texture atlas
	Image flippedAtlasImage = ImageBuilder::copyImage(atlasImage, true);
	Texture atlasTexture = Texture(
		flippedAtlasImage.data, flippedAtlasImage.width, flippedAtlasImage.height,
		GlImageFormat::Rgba, unit
	);
	TextureAtlas atlas = createAtlas(std::move(atlasTexture), data, rects);
	
	return atlas;
}

u32 TexturePacker::calculateStartingAtlasSize(const std::vector<TexRect>& rects)
{
	u64 maxSideSum = 0;
	u32 maxSide = 0;
	
	for (const TexRect& rect : rects)
	{
		u32 currentSide = std::max(rect.rect.size.x, rect.rect.size.y);

		maxSideSum += currentSide;

		if (maxSide < currentSide)
			maxSide = currentSide;
	}

	u32 meanSize = maxSideSum / sqrt(rects.size());
	meanSize += INTERVAL - meanSize % INTERVAL;
	maxSide += INTERVAL - maxSide % INTERVAL;

	return std::max(meanSize, maxSide);
}

bool TexturePacker::packRects(std::vector<TexRect>& rects, u32 size)
{
	if (size == 0)
		return false;
	
	u32 numRects = rects.size();
	u32 rowHeight = rects[0].rect.size.y;
	rects[0].rect.position = Point(0, 0);
	u32 i = 1;

	while (i < numRects)
	{
		TexRect& previous = rects[i - 1];
		TexRect& current = rects[i];
		
		Point placePos = previous.rect.position + Point(previous.rect.size.x, 0);
		bool exceedsWidth = placePos.x + current.rect.size.x >= size;
		if (exceedsWidth)
		{
			placePos = Point(0, placePos.y + rowHeight);
			rowHeight = current.rect.size.y;
			
			bool exceedsHeight = placePos.y + current.rect.size.y >= size;
			if (exceedsHeight)
			{
				//std::cout << "Failed to pack with size=" << size << "px.\n";
				return false;
			}
		}

		current.rect.position = placePos;

		i++;
	}

	//std::cout << "Successfully packed with size=" << size << "px.\n";
	return true;
}

u32 TexturePacker::packRectsUndershootCase(std::vector<TexRect>& rects, u32 size)
{
	bool successfullyPacked = false;

	while (!successfullyPacked)
	{
		size += INTERVAL;
		successfullyPacked = packRects(rects, size);
	}

	return size;
}

u32 TexturePacker::packRectsOvershootCase(std::vector<TexRect>& rects, u32 size)
{
	if (size <= INTERVAL)
		return size;

	u32 numRects = rects.size();
	std::vector<TexRect> previousRects;
	previousRects.resize(numRects);

	bool successfullyPacked = true;
	while (successfullyPacked)
	{
		previousRects = rects;
		size -= INTERVAL;
		successfullyPacked = packRects(rects, size);
	}
	
	rects = previousRects;

	return size + INTERVAL;
}

TextureAtlas TexturePacker::createAtlas(Texture&& texture, const std::vector<TexData>& data, const std::vector<TexRect>& rects)
{
	TextureAtlas atlas = TextureAtlas(std::move(texture), data.size());

	for (const TexRect& rect : rects)
	{
		// FIXME: BULLSHIT!
		atlas.addTexture(std::string(data[rect.id].name.data()), Texture2D(atlas.source_, rect.rect));
	}

	return atlas;
}

void TexturePacker::exportAtlas(const char* name, const Image& atlasImage, const std::vector<TexData>& data, const std::vector<TexRect>& rects)
{
	Path imagePath = FileManager::getAtlasImagePath(name);
	Path metaDataPath = FileManager::getAtlasMetaDataPath(name);

	ImageWriter::write(atlasImage, imagePath.path().data());

	json metaData
	{
		{"id", name},
		{"source", imagePath.path().data()}
	};

	for (const TexRect& rect : rects)
	{
		metaData["textures"][data[rect.id].name.data()] = {
			rect.rect.position.x,
			rect.rect.position.y,
			rect.rect.size.x,
			rect.rect.size.y
		};
	}

	std::ofstream metaDataOut = std::ofstream(metaDataPath.path().data());
	metaDataOut << std::setw(4) << metaData << std::endl;
}