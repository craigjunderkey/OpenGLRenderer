#pragma once
#include "Texture.h"
#include "Types.h"
#include "Rectangle.h"
#include "Point.h"

namespace Graphics
{
	class Texture2D
	{
	public:
		Texture2D(const Texture& source, Common::Rectangle region);
		vec4 uvCoords() const { return this->uvCoords_; }
		Common::Point size() const { return this->region_.size; }
		u32 id() const { return this->sourceId_; }

		static vec4 regionToUv(Common::Point totalSize, Common::Rectangle region);
		vec4 getSubregionUv(Common::Rectangle region) const;
		Texture2D makeSubtexture(Common::Rectangle subregion) const;
	
	private:
		// note: these members are heavier than is absolutely necessary
		// we could easily drop sourceId_ and the size component of region_
		// that'd make this guy 36 bytes instead of 44 bytes
		// then again, we pass references to the Texture2Ds
		// then again, if we load 1000 Texture2Ds, that's still ~43kb
		// then again, on the heap, ~43kb is pretty much nothing

		vec4 uvCoords_;
		Common::Rectangle region_;
		u32 sourceId_;
		Common::Point sourceSize_;
	};
}
