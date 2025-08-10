#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "VertexAttributeSets.h"
#include "GlErrorChecker.h"
#include "ErrorReporter.h"

using namespace Graphics;
using namespace Common;
using namespace AssetManagement;

SpriteBatch::SpriteBatch(const TextureAtlas& textureAtlas, ShaderEffectCache& effectCache, const std::string& defaultEffect, mat4 projectionTransform, size_t maxObjects)
	: view_(mat4(1.0f)),
	zoom_(mat4(1.0f)),
	projection_(projectionTransform),
	mesh_(createMesh()),
	textureAtlas_(textureAtlas),
	textureAtlasSource_(textureAtlas.source()),
	maxObjects_(maxObjects),
	effectCache_(effectCache),
	defaultEffectId_(effectCache.getEffectIndex(defaultEffect))
{
	// reserve space
	this->objects_.reserve(this->maxObjects_);
	this->effectInfo_.reserve(this->maxObjects_);
	this->effectUniformCaches_.resize(effectCache.numEffects());
}

SpriteBatch::~SpriteBatch() {}

void SpriteBatch::draw(const Texture2D& texture, vec2 position, SpriteDrawInfo info)
{
	EffectInfo effectInfo = EffectInfo(effectFromCstr(info.effect), info.effectUniforms);
	
	bool isDrawingSubregion = info.region.size.x != 0 && info.region.size.y != 0;
	if (isDrawingSubregion)
	{
		Texture2D subtexture = texture.makeSubtexture(info.region);
		mat4 model = createModel(subtexture, position, info);
		storeDrawCall(subtexture, std::move(model), effectInfo, info.flags, info.tint);
	}
	else
	{
		mat4 model = createModel(texture, position, std::move(info));
		storeDrawCall(texture, std::move(model), effectInfo, info.flags, info.tint);
	}
}

void SpriteBatch::draw(const std::string& textureName, vec2 position, SpriteDrawInfo info)
{
	const Texture2D& texture = this->textureAtlas_.get(textureName);
	draw(texture, position, info);
}

mat4 SpriteBatch::createModel(const Texture2D& texture, vec2 position, SpriteDrawInfo info)
{
	if (info.angle == 0)
	{
		mat4 model = glm::translate(mat4(1.0f), vec3(position.x, position.y, -1));
		model = glm::scale(std::move(model),
			vec3(texture.size().x * info.scale.x, texture.size().y * info.scale.y, 1.0f));
		return model;
	}
	else
	{
		mat4 model = glm::translate(mat4(1.0f), vec3(position.x, position.y, -1));
		model = glm::translate(std::move(model), vec3(info.pivotPoint.x, info.pivotPoint.y, 0));
		model = glm::rotate(std::move(model), info.angle, vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(std::move(model), vec3(-info.pivotPoint.x, -info.pivotPoint.y, 0));
		model = glm::scale(std::move(model),
			vec3(texture.size().x * info.scale.x, texture.size().y * info.scale.y, 1.0f));
		return model;
	}
}

void SpriteBatch::storeDrawCall(const Texture2D& texture, mat4 model, EffectInfo effectInfo, u8 drawFlags, ColorRgb tint)
{
	// warn if exceeding max objects
	if (this->objects_.size() >= maxObjects_)
		ErrorReporter::warn("SpriteBatch exceeded buffer size (" + std::to_string(maxObjects_) + "). Allocating more space!");

	// push the object into the array
#pragma warning(suppress: 28020)
	this->objects_.push_back(InstancedRenderObject(
		this->zoom_ * std::move(model), texture.uvCoords(), drawFlags, tint));
	this->effectInfo_.push_back(effectInfo);
}

void SpriteBatch::setZoomLevel(u8 zoomLevel)
{
	this->zoom_ = glm::scale(mat4(1.0f), vec3(zoomLevel, zoomLevel, 1));
}

void SpriteBatch::render()
{
	if (this->objects_.size() == 0)
		return;
	
	glDisable(GL_DEPTH_TEST);

	this->mesh_.bind();
	this->textureAtlasSource_.bind();

	// batch by current effect
	EffectInfo currentEffect = this->effectInfo_[0];
	u32 currentIndex = 1;
	u32 startIndex = 0;
	u32 batchSize = 0;
	
	for (u32 i = 0; i < this->objects_.size(); i++)
	{
		bool effectChanged = this->effectInfo_[i].effect != currentEffect.effect;
		bool propertiesChanged = this->effectInfo_[i].properties != nullptr;
		
		if (effectChanged || propertiesChanged)
		{
			// draw
			bool onlyPropertiesChanged = !effectChanged;
			bindAndUpdateEffect(currentEffect, onlyPropertiesChanged);
			bufferAndDraw(startIndex, batchSize);
			
			// reset
			startIndex = i;
			currentEffect = this->effectInfo_[i];
			batchSize = 1;
		}
		else
		{
			batchSize++;
		}
	}

	if (batchSize > 0)
	{
		bindAndUpdateEffect(currentEffect, false);
		bufferAndDraw(startIndex, batchSize);
	}
	
	this->objects_.clear();
	this->effectInfo_.clear();
}

void SpriteBatch::bufferAndDraw(u32 offsetIndex, u32 batchSize)
{
	if (batchSize == 0)
		return;
	
	this->mesh_.instanceVbo().bind(
		&this->objects_.data()[offsetIndex],
		batchSize * sizeof(InstancedRenderObject)
	);

	if (!this->mesh_.hasEbo())
		glDrawArraysInstanced(GL_TRIANGLES, 0, this->mesh_.count(), batchSize);
	else
		glDrawElementsInstanced(GL_TRIANGLES, this->mesh_.count(), GL_UNSIGNED_INT, 0, batchSize);
}

void SpriteBatch::setView(mat4 viewTransform)
{
	if (this->view_ != viewTransform)
	{
		for (UniformCache& cache : this->effectUniformCaches_)
		{
			cache.setOutdated(UniformCache::Uniform::View);
		}
	}

	this->view_ = std::move(viewTransform);
}

void SpriteBatch::setProjection(mat4& projectionTransform)
{
	if (this->projection_ != projectionTransform)
	{
		for (UniformCache& cache : this->effectUniformCaches_)
		{
			cache.setOutdated(UniformCache::Uniform::Projection);
		}
	}

	this->projection_ = projectionTransform;
}

InstancedMesh SpriteBatch::createMesh()
{
	f32 vertices[] = {
			1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
			1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
			0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.0f, 1.0f
	};

	u32 indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	return InstancedMesh(
		(void*)vertices,
		sizeof(vertices),
		indices,
		6,
		*VertexAttributeSets::POSITION_UV,
		*VertexAttributeSets::TRANSFORM_UV_UINT
	);
}

i32 SpriteBatch::effectFromCstr(const char* effect)
{
	if (effect == nullptr)
		return this->defaultEffectId_;
	else
		return this->effectCache_.getEffectIndex(std::string(effect));
}

void SpriteBatch::bindAndUpdateEffect(EffectInfo info, bool onlyPropertiesChanged)
{
	if (info.effect == ShaderEffectCache::NO_EFFECT)
		return;
	
	ShaderProgram& program = this->effectCache_.getEffect(info.effect).program_;
	
	if (!onlyPropertiesChanged)
	{
		program.use();
		
		UniformCache& cache = this->effectUniformCaches_[info.effect];

		if (cache.isOutdated(UniformCache::Uniform::TexUnit))
		{
			program.uniforms().set("atlas", this->textureAtlasSource_.unit());
			cache.setUpdated(UniformCache::Uniform::TexUnit);
		}

		if (cache.isOutdated(UniformCache::Uniform::View))
		{
			program.uniforms().set("v", this->view_);
			cache.setUpdated(UniformCache::Uniform::View);
		}

		if (cache.isOutdated(UniformCache::Uniform::Projection))
		{
			program.uniforms().set("p", this->projection_);
			cache.setUpdated(UniformCache::Uniform::Projection);
		}
	}
	
	if (info.properties != nullptr)
	{
		info.properties->execute(program.uniforms());
		delete info.properties;
	}
}