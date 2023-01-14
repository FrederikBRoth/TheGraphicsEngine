#include <entities/Mesh.h>

Mesh::Mesh(std::vector<float> vertices, int triangleCount)
{
	this->vao = new VertexArray(vertices);
	this->triangleCount = triangleCount;
	this->vao->init(VertexArrayConfig(8, true, true, TRIANGLE));
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


