#include <includes/rendering/VertexArray.h>

VertexArray::VertexArray(float* vertices, int triangleCount)
{
	this->vbo = new VertexBuffer(vertices, triangleCount);
	glGenVertexArrays(1, &this->ID);
}

VertexArray::~VertexArray()
{
	delete this->vbo;
}

void VertexArray::init(int size)
{
	this->vbo->init();
	glBindVertexArray(this->ID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void VertexArray::bind()
{
	glBindVertexArray(this->ID);
}
