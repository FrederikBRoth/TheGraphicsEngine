#ifndef MESH_H
#define MESH_H
#include <rendering/VertexArray.h>
class Mesh
{
public:
	VertexArray* vao;
	int triangleCount;
	Mesh(float* vertices, int triangleCount);
	~Mesh();
	void render();
};
#endif
