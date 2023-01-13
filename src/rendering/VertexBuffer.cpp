#include <rendering/VertexBuffer.h>

VertexBuffer::VertexBuffer(std::vector<float> vertices)
{
	this->vertices = vertices;
	glGenBuffers(1, &this->ID);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->ID);
}

void VertexBuffer::init()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size()* sizeof(float), &vertices[0], GL_STATIC_DRAW);
}
