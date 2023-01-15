#include <controls/LineTrace.h>
#include <world/WorldUtils.h>
glm::vec3 LineTrace::trace(glm::vec3& playerPos, glm::vec3& playerFront, ChunkController* cc)
{
    for (int i = 1; i < (int)DISTANCE / STEPSIZE; i++) {
        glm::vec3 step = (playerPos + (playerFront * ((float)i * STEPSIZE)));
        int worldX = floor((step.x * 2.0f));
        int worldY = floor((step.y * 2.0f));
        int worldZ = floor((step.z * 2.0f));
        glm::vec3 worldCoord = glm::vec3(worldX, worldY, worldZ);
        if (cc->removeBlock(worldX, worldY, worldZ)) {
            return worldCoord;            
        }
    };
    return glm::vec3(0.0f, 0.0f, 0.0f);

}

