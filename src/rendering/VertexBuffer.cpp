#include <rendering/VertexBuffer.h>

VertexBuffer::VertexBuffer(float* vertices, int triangleCount)
{
	this->vertices.reserve(triangleCount * 8);
	for (int i = 0; i < triangleCount * 8; i++) {
		this->vertices.emplace_back(vertices[i]);
	}
	glGenBuffers(1, &this->ID);
}

void VertexBuffer::init()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size()* sizeof(float), &vertices[0], GL_STATIC_DRAW);
}
