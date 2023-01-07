#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include <glad/glad.h>
#include <vector>
class VertexBuffer
{
public:
	unsigned int ID;
	std::vector<float> vertices;
	VertexBuffer(std::vector<float> vertices);
	void init();
};
#endif
