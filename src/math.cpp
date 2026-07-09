#include "math.h"

float math::distanceSquared(glm::vec3 v1, glm::vec3 v2)
{
    float dX = math::squareFloat(v2.x - v1.x);
    float dY = math::squareFloat(v2.y - v1.y);
    float dZ = math::squareFloat(v2.z - v1.z);

    return (dX + dY + dZ);
}

float math::distanceSquared2D(glm::vec2 v1, glm::vec2 v2)
{
    float netX = math::squareFloat(v2.x - v1.x);
    float netY = math::squareFloat(v2.y - v1.y);

    return netX + netY;
}

float math::earthMassToKG(float mass)
{
    const long massOfEarth = 5.9722e24L;

    return massOfEarth * mass;
}


float math::calculateSchwarzschildRadius(float objectMass)
{
    const long gravitationalConstant = 6.67e-11L;
    const long speedOfLight = 299792458L;

    return (2.0f * gravitationalConstant * objectMass) / (speedOfLight * speedOfLight);

}