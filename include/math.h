#pragma once
#include "dependencies.h"

class math
{
public:
    static float squareFloat(float number) { return (number * number); };
    static float distanceSquared(glm::vec3 v1, glm::vec3 v2);
    static float distanceSquared2D(glm::vec2 v1, glm::vec2 v2);

    static float earthMassToKG(float earthMass);
    static float gigameterToMeter(float gigameter) { return gigameter * 1e9L; }

    //IS IN METERS!
    static float calculateSchwarzschildRadius(float mass);
};