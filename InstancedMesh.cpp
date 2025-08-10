#include <GL/glew.h>
#include "InstancedMesh.h"

using namespace Graphics;

InstancedMesh::InstancedMesh(const void* staticData, u32 staticDataSize, const VertexAttributeSet& staticAttributes, const VertexAttributeSet& instanceAttributes)
	: vao_(VertexArrayObject()),
	staticVbo_(VertexBufferObject()),
	staticEbo_(ElementBufferObject::makeEmpty()),
	instanceVbo_(VertexBufferObject())
{
	this->count_ = staticDataSize / staticAttributes.size_;

	this->vao_.bind();

	// bind static attributes
	this->staticVbo_.bind(staticData, staticDataSize);
	staticAttributes.bind();
	
	// bind instance attributes
	this->instanceVbo_.bind();
	u32 instanceStart = staticAttributes.numGlAttributes_;
	instanceAttributes.bind(instanceStart);
	u32 totalAttributes = staticAttributes.numGlAttributes_ + instanceAttributes.numGlAttributes_;
	for (int i = instanceStart; i < totalAttributes; i++)
	{
		glVertexAttribDivisor(i, 1);
	}
}

InstancedMesh::InstancedMesh(const void* staticData, u32 staticDataSize, const u32* staticIndices, u32 staticIndexCount, const VertexAttributeSet& staticAttributes, const VertexAttributeSet& instanceAttributes)
	: vao_(VertexArrayObject()),
	staticVbo_(VertexBufferObject()),
	staticEbo_(ElementBufferObject()),
	instanceVbo_(VertexBufferObject())
{
	this->count_ = staticIndexCount;

	this->vao_.bind();
	
	// bind static attributes
	this->staticVbo_.bind(staticData, staticDataSize);
	this->staticEbo_.bind(staticIndices, staticIndexCount);
	staticAttributes.bind();

	// bind instance attributes
	this->instanceVbo_.bind();
	u32 instanceStart = staticAttributes.numGlAttributes_;
	instanceAttributes.bind(instanceStart);
	u32 totalAttributes = staticAttributes.numGlAttributes_ + instanceAttributes.numGlAttributes_;
	for (int i = instanceStart; i < totalAttributes; i++)
	{
		glVertexAttribDivisor(i, 1);
		//std::cout << "glVertexAttribDivisor( " << i << " " << 1 << " );\n";
	}
}

bool InstancedMesh::hasEbo() const
{
	return !this->staticEbo_.isEmpty();
}

void InstancedMesh::bind()
{
	vao_.bind();
}

void InstancedMesh::bind(const void* instanceData, u32 instanceDataSize)
{
	vao_.bind();
	this->instanceVbo_.bind(instanceData, instanceDataSize);
}