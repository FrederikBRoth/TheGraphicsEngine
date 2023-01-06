#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include <glad/glad.h>
#include <vector>
class VertexBuffer
{
public:
	unsigned int ID;
	std::vector<float> vertices;
	VertexBuffer(float* vertices, int triangleCount);
	void init();
};
#endif
