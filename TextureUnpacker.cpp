#include <fstream>
#include "TextureUnpacker.h"
#include "Texture.h"
#include "FileManager.h"
#include "json.hpp"

using namespace AssetManagement;
using namespace Common;
using namespace Graphics;

using json = nlohmann::json;

TextureAtlas TextureUnpacker::importAtlas(const std::string& moduleName, Graphics::Texture::Unit textureUnit)
{
	// TODO: retrieve file from source field
	Texture texture = Texture::fromFile(
		FileManager::getAtlasImagePath(moduleName).c_str(), textureUnit);

	// parse atlas json
	std::ifstream metaDataFile = std::ifstream(FileManager::getAtlasMetaDataPath(moduleName));
	json metaData = json::parse(metaDataFile);

	// create and fill atlas
	TextureAtlas atlas = TextureAtlas(std::move(texture), metaData["textures"].size());
	for (const auto& [name, rect] : metaData["textures"].items())
	{
		Rectangle region = Rectangle(rect[0], rect[1], rect[2], rect[3]);
		atlas.addTexture(name, Texture2D(atlas.source_, region));
	}

	return atlas;
}