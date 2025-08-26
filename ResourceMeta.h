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
		ShaderEffect,
		PackageDefinition
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

	class ResourceMeta
	{
	public:
		ResourceMeta() = delete;

		static void initialize()
		{
			// TEXTURE
			resources_[(u32)ResourceType::Texture] = ResourceDescription(
				"Texture",
				"Textures",
				nullptr, // compiler (copier)!
				nullptr, // loader!
				nullptr  // null linker!
			);
			
			// TEXTURE ATLAS
			resources_[(u32)ResourceType::TextureAtlas] = ResourceDescription(
				"Texture Atlas",
				"TextureAtlases",
				nullptr, // compiler (texture packer)!
				nullptr, // loader!
				nullptr  // linker!
			);
			
			// SHADER
			resources_[(u32)ResourceType::Shader] = ResourceDescription(
				"Shader",
				"Shaders",
				nullptr, // compiler (copier)!
				nullptr, // loader!
				nullptr  // null linker!
			);
			
			// SHADER EFFECT
			resources_[(u32)ResourceType::ShaderEffect] = ResourceDescription(
				"Shader Effect",
				"ShaderEffects",
				nullptr, // compiler (copier)!
				nullptr, // loader!
				nullptr  // linker!
			);
			
			// PACKAGE DEFINITION
			resources_[(u32)ResourceType::PackageDefinition] = ResourceDescription(
				"Package Definition",
				"PackageDefinitions",
				nullptr, // compiler (copier)!
				nullptr, // loader!
				nullptr  // null linker!
			);
		}

	private:
		static const u32 NUM_RESOURCES = 5;

		static ResourceDescription resources_[NUM_RESOURCES];
	};
}
