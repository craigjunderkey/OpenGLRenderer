#pragma once

namespace Graphics
{
	class Mesh;
	
	class Meshes
	{
	public:
		static Mesh* TRIANGLE;
		static Mesh* QUAD;

		static void initialize();
	
	private:
		Meshes() = delete;
	};
}
