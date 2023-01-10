#include <rendering/IndexBuffer.h>

IndexBuffer::IndexBuffer(std::vector<unsigned short> indices)
{
	this->indices = indices;
	glGenBuffers(1, &this->ID);
}


void IndexBuffer::init()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}
