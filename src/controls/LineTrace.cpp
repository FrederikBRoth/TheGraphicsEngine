#include <controls/LineTrace.h>
#include <world/WorldUtils.h>
BlockType LineTrace::trace(glm::vec3& playerPos, glm::vec3& playerFront, ChunkController* cc)
{
    BlockType hit;
    for (int i = 1; i < (int)DISTANCE / STEPSIZE; i++) {
        glm::vec3 step = (playerPos + (playerFront * ((float)i * STEPSIZE)));
        int worldX = floor((step.x * 2.0f));
        int worldY = floor((step.y * 2.0f));
        int worldZ = floor((step.z * 2.0f));
        glm::vec3 worldCoord = glm::vec3(worldX, worldY, worldZ);
        hit = cc->removeBlock(worldX, worldY, worldZ);
        if (hit != BlockType::NOTHING)
            break;
    };
    return hit;
}
glm::vec3 LineTrace::detailedTrace(glm::vec3& playerPos, glm::vec3& playerFront, ChunkController* cc)
{
    Block* hit;
    for (int i = 1; i < (int)DISTANCE / STEPSIZE; i++) {
        glm::vec3 step = (playerPos + (playerFront * ((float)i * STEPSIZE)));
        int worldX = floor((step.x * 2.0f));
        int worldY = floor((step.y * 2.0f));
        int worldZ = floor((step.z * 2.0f));
        glm::vec3 worldCoord = glm::vec3(worldX, worldY, worldZ);
        hit = cc->getBlock(worldX, worldY, worldZ);
        if (hit != nullptr) {
            glm::vec3 formatedCoord = glm::vec3(std::round(step.x * 100.0f) / 100.0f, std::round(step.y * 100.0f) / 100.0f, std::round(step.z * 100.0f) / 100.0f);
            //return { step.x, step.y, step.z };
            return formatedCoord;
        }
    };

    return { 0,0,0 };
}

