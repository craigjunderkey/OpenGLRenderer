#pragma once
#include <array>
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

	bool isPackable(PreResourceType preResource)
	{
		bool isPackable = true;
		
		if (preResource == PreResourceType::PackageDefinition)
		{
			isPackable = false;
		}

		return isPackable;
	}

	struct PreResourceDescription
	{
		//PreResourceDescription() {}
		PreResourceDescription(PreResourceType type, const char* name,
			const char* pkgModule, const char* ext1, const char* ext2 = nullptr)
		{
			this->name = name;
			this->pkgModule = pkgModule;
			this->extension[0] = ext1;
			this->extension[1] = ext2;
		}

		const char* name = nullptr;
		const char* pkgModule = nullptr;
		const char* extension[2] = {nullptr};
		PreResourceType type;
	};

	class PreResourceMeta
	{
	public:
		static const u32 NUM_PRE_RESOURCES = 5;
		static const u32 NUM_PACKABLE_PRE_RESOURCES = 4;

		PreResourceMeta() = delete;

		static void initialize()
		{
			// SPRITE TEXTURE
			preResources_[(u32)PreResourceType::SpriteTexture] = PreResourceDescription(
				PreResourceType::SpriteTexture, "Sprite Texture", "SpriteTextures", "png", "ase"
			);

			// MESH TEXTURE
			preResources_[(u32)PreResourceType::MeshTexture] = PreResourceDescription(
				PreResourceType::MeshTexture, "Mesh Texture", "MeshTextures", "png", "ase"
			);

			// SHADER
			preResources_[(u32)PreResourceType::Shader] = PreResourceDescription(
				PreResourceType::Shader, "Shader", "Shaders", "glsl"
			);

			// SHADER EFFECT
			preResources_[(u32)PreResourceType::ShaderEffect] = PreResourceDescription(
				PreResourceType::ShaderEffect, "Shader Effect", "ShaderEffects", "effect"
			);

			// PACKAGE DEFINITION
			preResources_[(u32)PreResourceType::PackageDefinition] = PreResourceDescription(
				PreResourceType::PackageDefinition, "Package Definition", "PackageDefinitions", "pack"
			);
		}

		static const PreResourceDescription* getPreResource(PreResourceType type)
		{
			return &preResources_[(u32)type];
		}

	private:
		using PreResourceArray = std::array<PreResourceDescription, NUM_PRE_RESOURCES>;
		static PreResourceArray preResources_;

	public:
		static const PreResourceArray& getPreResources() { return preResources_; }
	};
}
