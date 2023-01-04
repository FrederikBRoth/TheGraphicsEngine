#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include "../includes/entities/Entity.h"

class VertexBuffer
{
public:
	unsigned int ID;
	Entity* e;
	VertexBuffer(unsigned int ID, Entity* e);
	void init();
};
#endif
