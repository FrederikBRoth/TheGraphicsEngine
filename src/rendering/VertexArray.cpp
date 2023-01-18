#include <rendering/VertexArray.h>

VertexArray::VertexArray(std::vector<float>& vertices)
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

void VertexArray::init(VertexArrayConfig config)
{
	int index = 0;
	glBindVertexArray(this->ID);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, config.size * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
	index++;
	if (config.normals) {
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, config.size * sizeof(float), (void*)((index*3) * sizeof(float)));
		glEnableVertexAttribArray(index);
		index++;
	}
	if (config.texture) {
		glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, config.size * sizeof(float), (void*)((index * 3) * sizeof(float)));
		glEnableVertexAttribArray(index);
		index++;
	}


}

void VertexArray::bind()
{
	glBindVertexArray(this->ID);
}


