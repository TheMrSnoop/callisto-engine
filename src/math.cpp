#include "math.h"

float math::distanceSquared(glm::vec3 v1, glm::vec3 v2)
{
    float dX = math::squareFloat(v2.x - v1.x);
    float dY = math::squareFloat(v2.y - v1.y);
    float dZ = math::squareFloat(v2.z - v1.z);

    return (dX + dY + dZ);
}