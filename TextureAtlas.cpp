#include "TextureAtlas.h"
#include "ErrorReporter.h"

using namespace Graphics;
using namespace Common;
using namespace AssetManagement;

TextureAtlas::TextureAtlas(StringId source, u32 capacity)
	: source_((Graphics::Texture*)source.toPtr()),
	textures_(StringIdTable<Texture2D>(capacity))
{
}

const Texture2D& TextureAtlas::get(StringId textureId) const
{
	const Texture2D* tex = this->textures_.get(textureId);

	if (tex != nullptr)
	{
		return *tex;
	}
	else
	{
		ErrorReporter::panic("Tried to retrieve but couldn't find "
			+ std::string(lookupString(textureId)) + ".");
	}
}

void TextureAtlas::addTexture(StringId textureId, Texture2D texture)
{
	this->textures_.add(textureId, std::move(texture));
}
