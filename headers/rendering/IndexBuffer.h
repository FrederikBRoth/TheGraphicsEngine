#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include <vector>
#include <glad/glad.h>

class IndexBuffer
{
	unsigned int ID;
	std::vector<unsigned int> indices;
	IndexBuffer(std::vector<unsigned int> indices);
	void init();
	void bind();
};
#endif // !INDEXBUFFER_H
