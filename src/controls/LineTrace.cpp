#include <controls/LineTrace.h>


BlockType LineTrace::remove(glm::vec3& playerPos, glm::vec3& playerFront, ChunkController* cc)
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
glm::vec3 LineTrace::create(glm::vec3& playerPos, glm::vec3& playerFront, ChunkController* cc, Player* player)
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
            float minX = worldX / 2.0f;
            float maxX = worldX / 2.0f + 0.5f;
            float minY = worldY / 2.0f;
            float maxY = worldY / 2.0f + 0.5f;
            float minZ = worldZ / 2.0f;
            float maxZ = worldZ / 2.0f + 0.5f;
            glm::vec3 relativeCoord = { 0,0,0 };
            if (tge::difference(minX, formatedCoord.x) < 0.01)
                relativeCoord = glm::vec3(-1, 0, 0);
            if(tge::difference(maxX, formatedCoord.x) < 0.01)
                relativeCoord = glm::vec3(1, 0, 0);
            if(tge::difference(minY, formatedCoord.y) < 0.01)
                relativeCoord = glm::vec3(0, -1, 0);
            if(tge::difference(maxY, formatedCoord.y) < 0.01)
                relativeCoord = glm::vec3(0, 1, 0);
            if(tge::difference(minZ, formatedCoord.z) < 0.01)
                relativeCoord = glm::vec3(0, 0, -1);
            if(tge::difference(maxZ, formatedCoord.z) < 0.01)
                relativeCoord = glm::vec3(0, 0, 1);
            BlockType type = player->inventory->inventory[player->inventory->selected];
            if (type != BlockType::NOTHING) {
                cc->updateBlock(worldX, worldY, worldZ, relativeCoord, player->inventory->inventory[player->inventory->selected]);
                player->inventory->removeItem();

            }
            return relativeCoord;
        }
    };

    return { 0,0,0 };
}


