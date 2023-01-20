#include <chunk/terrain-generation/TerrainNoise.h>

TerrainNoise::TerrainNoise()
{
	siv::PerlinNoise::seed_type seed = 123456u;
	perlin = siv::PerlinNoise(seed);
}

TerrainNoise::TerrainNoise(unsigned int seed)
{
	perlin = siv::PerlinNoise(seed);
}

std::vector<int> TerrainNoise::generateNoiseMap(glm::vec3& position, int magnitude, double multiplier)
{
	std::vector<int> noiseMap;
	for (int z = position.z; z < position.z + CHUNKSIZE_Z; z++) {
		for (int x = position.x; x < position.x + CHUNKSIZE_X; x++) {
			double n = perlin.noise2D((x * multiplier), (z * multiplier));
			
			noiseMap.push_back(floor(tge::logisticInterpolation(magnitude, -0.2f, n*(float)magnitude-2.0f)));
		}
	}
	return noiseMap;
}
