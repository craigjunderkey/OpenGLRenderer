#pragma once
#include <array>
#include "ResourceCompiler.h"
#include "ResourceLoader.h"
#include "ResourceLinker.h"

namespace Resources
{
	enum class ResourceType
	{
		Texture,
		TextureAtlas,
		Shader,
		ShaderEffect
	};

	struct ResourceDescription
	{
		ResourceDescription() {}
		
		ResourceDescription(const char* name, const char* directory,
			ResourceCompiler* compiler, ResourceLoader* loader, ResourceLinker* linker)
			: name(name), directory(directory), compiler(compiler), loader(loader), linker(linker)
		{}

		const char* name = nullptr;
		const char* directory = nullptr;
		ResourceCompiler* compiler = nullptr;
		ResourceLoader* loader = nullptr;
		ResourceLinker* linker = nullptr;
	};

	//struct DirectoryDescription
	//{
	//	const char* directory;
	//	ResourceDescription* resource;
	//};

	//enum class DirectoryType
	//{
	//	Textures,
	//	TextureAtlases,
	//	Shaders,
	//	ShaderEffects
	//};
	
	class ResourceMeta
	{
	public:
		ResourceMeta() = delete;

		static void initialize()
		{
			resources_[(u32)ResourceType::Texture] = ResourceDescription();
			resources_[(u32)ResourceType::TextureAtlas] = ResourceDescription();
			resources_[(u32)ResourceType::Shader] = ResourceDescription();
			resources_[(u32)ResourceType::ShaderEffect] = ResourceDescription();
		}

	private:
		static const u32 NUM_RESOURCES = 4;

		static ResourceDescription resources_[NUM_RESOURCES];
	};
}
