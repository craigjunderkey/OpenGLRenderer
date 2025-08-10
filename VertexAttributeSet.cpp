#include "VertexAttributeSet.h"
#include "VertexAttribute.h"

using namespace Graphics;

VertexAttributeSet& VertexAttributeSet::add(VertexAttribute attribute)
{
	this->attributes_.push_back(BoundVertexAttribute(attribute, this->size_));
	this->size_ += attribute.size();
	this->numGlAttributes_ += attribute.numGlAttributes();
	return *this;
}

void VertexAttributeSet::bind() const
{
	bind(0);
}

void VertexAttributeSet::bind(u32 offset) const
{
	u32 attributeIndex = offset;

	for (int i = 0; i < this->attributes_.size(); i++)
	{
		const BoundVertexAttribute& current = this->attributes_[i];
		current.attribute_.bind(attributeIndex, this->size_, current.offset_);
		attributeIndex += current.attribute_.numGlAttributes();
	}
}

VertexAttributeSet& VertexAttributeSet::append(const VertexAttributeSet& attributeSet)
{
	this->attributes_.reserve(this->size_ + attributeSet.size_);
	this->attributes_.insert(
		this->attributes_.end(),
		attributeSet.attributes_.begin(),
		attributeSet.attributes_.end()
	);
	return *this;
}
