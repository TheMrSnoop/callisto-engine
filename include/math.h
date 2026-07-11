#pragma once
#include "dependencies.h"

class math
{
public:
    static float squareFloat(float number) { return (number * number); };
    static float distanceSquared(glm::vec3 v1, glm::vec3 v2);
    static float distanceSquared2D(glm::vec2 v1, glm::vec2 v2);

    static double earthMassToKG(double earthMass);
    static double gigameterToMeter(float gigameter) { return gigameter * 1e9L; }

    //IS IN METERS!
    static double calculateSchwarzschildRadius(double mass);

    //formula already handles unit conversions so no worry!
    static double calculateSpaceTimeDisplacement(double mass, double radius);
};