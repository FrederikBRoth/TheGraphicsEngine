#include <rendering/VertexArray.h>

VertexArray::VertexArray(std::vector<float> vertices)
{
	this->vbo = new VertexBuffer(vertices);
	glGenVertexArrays(1, &this->ID);
	this->vbo->init();

}

VertexArray::~VertexArray()
{
	delete this->vbo;
	glDeleteVertexArrays(1, &this->ID);
}

void VertexArray::init(int size)
{
	glBindVertexArray(this->ID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void VertexArray::bind()
{
	glBindVertexArray(this->ID);
}


