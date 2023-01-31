#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include <vector>
#include <glad/glad.h>

class IndexBuffer
{
public:
	unsigned int ID;
	std::vector<unsigned short> indices;
	IndexBuffer(std::vector<unsigned short>& indices);
	~IndexBuffer();
	void init();
	void bind();
};
#endif // !INDEXBUFFER_H
