#pragma once
#include "Types.h"

namespace Resources
{
	enum class PreResourceType
	{
		SpriteTexture,
		MeshTexture,
		Shader,
		ShaderEffect,
		PackageDefinition
	};

	struct PreResourceDescription
	{
		PreResourceDescription() {}
		PreResourceDescription(const char* name, const char* pkgModule, const char* ext1, const char* ext2 = nullptr)
		{
			this->name = name;
			this->pkgModule = pkgModule;
			this->extension[0] = ext1;
			this->extension[1] = ext2;
		}

		const char* name = nullptr;
		const char* pkgModule = nullptr;
		const char* extension[2] = {nullptr};
	};

	class PreResourceMeta
	{
	public:
		static const u32 NUM_PRE_RESOURCES = 5;

		PreResourceMeta() = delete;

		static void initialize()
		{
			// SPRITE TEXTURE
			preResources_[(u32)PreResourceType::SpriteTexture] = PreResourceDescription(
				"Sprite Texture", "SpriteTextures", "png", "ase"
			);

			// MESH TEXTURE
			preResources_[(u32)PreResourceType::MeshTexture] = PreResourceDescription(
				"Mesh Texture", "MeshTextures", "png", "ase"
			);

			// SHADER
			preResources_[(u32)PreResourceType::Shader] = PreResourceDescription(
				"Shader", "Shaders", "glsl"
			);

			// SHADER EFFECT
			preResources_[(u32)PreResourceType::ShaderEffect] = PreResourceDescription(
				"Shader Effect", "ShaderEffects", "effect"
			);

			// PACKAGE DEFINITION
			preResources_[(u32)PreResourceType::PackageDefinition] = PreResourceDescription(
				"Package Definition", "PackageDefinitions", "pack"
			);
		}

		static const PreResourceDescription* getPreResources()
		{
			return preResources_;
		}

		static const PreResourceDescription* getPreResource(PreResourceType type)
		{
			return &preResources_[(u32)type];
		}

	private:
		static PreResourceDescription preResources_[NUM_PRE_RESOURCES];
	};
}
