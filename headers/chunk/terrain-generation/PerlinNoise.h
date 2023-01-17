

#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <vector>
#include <perlinNoise/PerlinNoise.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <world/Constants.h>
class PerlinNoise {
private:
	siv::PerlinNoise perlin;
public:
	PerlinNoise();
	PerlinNoise(unsigned int seed);
	std::vector<int> generateNoiseMap(glm::vec3& position, int magnitude, double multiplier);

};

#endif