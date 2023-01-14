#include <controls/LineTrace.h>

glm::vec3 LineTrace::trace(glm::vec3 playerPos, glm::vec3 playerFront)
{
    glm::vec3 temp = (playerPos * playerFront) + DISTANCE;
    std::vector<float> vertices;
    vertices.emplace_back(playerPos.x);
    vertices.emplace_back(playerPos.y);
    vertices.emplace_back(playerPos.z);

    vertices.emplace_back(temp.x);
    vertices.emplace_back(temp.y);
    vertices.emplace_back(temp.z);

    Line* line = new Line(vertices, 2);
    line->render();
    return glm::vec3(floor((temp.x * 2.0f)), floor((temp.y * 2.0f)), floor((temp.z * 2.0f)));
}

