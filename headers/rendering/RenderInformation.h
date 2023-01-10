#ifndef RENDERINFORMATION_H
#define RENDERINFORMATION_H
#include <vector>
struct RenderInformation {
	std::vector<float> vertices;
	std::vector<unsigned short> indices;
};
#endif // !RENDERINFORMATION_H
