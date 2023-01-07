#include <entities/Mesh.h>

Mesh::Mesh(float* vertices, int triangleCount)
{
	this->vao = new VertexArray(vertices, triangleCount);
	this->triangleCount = triangleCount;
	this->vao->init(8);
}

Mesh::~Mesh()
{
	delete this->vao;
}

void Mesh::render()
{
	this->vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, this->triangleCount);
}


