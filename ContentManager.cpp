#include "ContentManager.h"
#include "ErrorReporter.h"
#include "TexturePacker.h"
#include "TextureUnpacker.h"
#include "FileManager.h"
#include "ShaderEffectCache.h"
#include "Locator.h"

using namespace Graphics;
using namespace Common;
using namespace AssetManagement;

ContentManager::ContentManager(bool forceRebuild)
	: spriteAtlas_(loadTextureAtlas(FileManager::SPRITE_ATLAS, Texture::Unit::SpriteTextureAtlas, forceRebuild)),
	meshAtlas_(loadTextureAtlas(FileManager::MESH_ATLAS, Texture::Unit::MeshTextureAtlas, forceRebuild)),
	fx_(buildFxCache())
{
}

TextureAtlas ContentManager::loadTextureAtlas(const char* moduleName, Graphics::Texture::Unit textureUnit, bool forceRebuild)
{
	bool isImportingAtlas = !forceRebuild
		&& Locator::fileSystem().fileExists(FileManager::getAtlasImagePath(moduleName))
		&& Locator::fileSystem().fileExists(FileManager::getAtlasMetaDataPath(moduleName));

	if (isImportingAtlas)
	{
		return TextureUnpacker::importAtlas(moduleName, textureUnit);
	}
	else
	{
		return buildTextureAtlas(moduleName, textureUnit);
	}
}

TextureAtlas ContentManager::buildTextureAtlas(const char* moduleName, Graphics::Texture::Unit textureUnit)
{
	std::vector<Path> filePaths = FileManager::getAllFilesFromModule(moduleName);
	bool hasAnyTextures = filePaths.size() > 0;

	if (hasAnyTextures)
	{
		return TexturePacker::pack(filePaths, textureUnit, moduleName, true);
	}
	else
	{
		ErrorReporter::warn("No textures found in " + std::string(moduleName) + ". Creating an empty atlas.");
		return TextureAtlas(Texture(nullptr, 0, 0, GlImageFormat::Rgba, textureUnit), 0);
	}
}

ShaderCache ContentManager::buildShaderCache()
{
	std::vector<Path> filePaths = FileManager::getAllFilesFromModule(FileManager::SHADERS);
	size_t numShaders = filePaths.size();
	ShaderCache cache = ShaderCache(numShaders);

	for (const Path& path : filePaths)
	{
		cache.cacheShader(path);
	}

	std::cout << "Compiled and cached " << numShaders << " shaders.\n";

	return cache;
}

ShaderEffectCache ContentManager::buildFxCache()
{
	ShaderCache shaderCache = buildShaderCache();

	std::vector<Path> filePaths = FileManager::getAllFilesFromModule(FileManager::SHADER_EFFECTS);
	size_t numFx = filePaths.size();
	ShaderEffectCache fxCache = ShaderEffectCache(numFx);

	for (const Path& path : filePaths)
	{
		fxCache.cacheShaderEffect(shaderCache, path);
	}

	std::cout << "Assembled " << numFx << " shader effects.\n";

	return fxCache;
}