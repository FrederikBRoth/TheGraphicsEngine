#ifndef LINE_H
#define LINE_H
#include <entities/IMesh.h>
#include <rendering/IndexBuffer.h>

class Line : public IMesh
{
public:
	int lineCount;
	Line(std::vector<float> vertices, int lineCount);
	~Line();
	virtual void render() override;
};
#endif
