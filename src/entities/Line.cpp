#include <entities/Line.h>

Line::Line(std::vector<float> vertices, int lineCount)
{
	this->vao = new VertexArray(vertices);
	this->lineCount = lineCount;
	this->vao->init(VertexArrayConfig(3, false, false, LINE));
}

Line::~Line()
{
	delete this->vao;
}

void Line::render()
{
	this->vao->bind();
	glDrawArrays(GL_LINES, 0, this->lineCount);
}


