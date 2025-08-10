#include "Texture2D.h"

using namespace Graphics;
using namespace Common;

Texture2D::Texture2D(const Texture& source, Rectangle region)
	: region_(region),
	sourceId_(source.id()),
	sourceSize_(source.size()),
	uvCoords_(regionToUv(source.size(), region))
{
}

vec4 Texture2D::regionToUv(Point totalSize, Rectangle region)
{
	// do this to avoid eating into neighboring sprites
	float texelX = 0.5f / (f32)totalSize.x;
	float texelY = 0.5f / (f32)totalSize.y;

	vec4 uv = vec4(
		(f32)(region.position.x + texelX) / (f32)totalSize.x,					// x start
		(f32)(region.position.y + texelY) / (f32)totalSize.y,					// y start
		(f32)(region.position.x + region.size.x - texelX) / (f32)totalSize.x,	// x end
		(f32)(region.position.y + region.size.y - texelY) / (f32)totalSize.y	// y end
	);

	return uv;
}

vec4 Texture2D::getSubregionUv(Rectangle region) const
{
	assert(region.position.x + region.size.x <= this->region_.size.x
		&& region.position.y + region.size.y <= this->region_.size.y);

	Rectangle newRegion = Rectangle(
		this->region_.position.x + region.position.x,
		this->region_.position.y + region.position.y,
		region.size.x,
		region.size.y
	);

	return regionToUv(this->sourceSize_, newRegion);
}

Texture2D Texture2D::makeSubtexture(Rectangle subregion) const
{
	Texture2D subTexture = *this;
	subTexture.uvCoords_ = this->getSubregionUv(subregion);
	subTexture.region_ = subregion;
	return subTexture;
}
