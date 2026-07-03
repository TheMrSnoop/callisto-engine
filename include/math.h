#pragma once
#include "dependencies.h"

class math
{
public:
    static float squareFloat(float number) { return (number * number); };
    static float distanceSquared(glm::vec3 v1, glm::vec3 v2);
};