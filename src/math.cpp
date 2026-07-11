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

double math::earthMassToKG(double mass)
{
    const double massOfEarth = 5.9722e24L;

    return massOfEarth * mass;
}


double math::calculateSchwarzschildRadius(double objectMass)
{
    const double gravitationalConstant = 6.67e-11L;
    const double speedOfLight = 299792458L;

    return (2.0f * gravitationalConstant * earthMassToKG(objectMass)) / (speedOfLight * speedOfLight);

}


double math::calculateSpaceTimeDisplacement(double mass, double radius)
{
    double schwarzschild = calculateSchwarzschildRadius(mass);
    double radiusMeters  = gigameterToMeter(radius);
    double difference    = radiusMeters - schwarzschild;

    double falloff = 1.0 / (radiusMeters * radiusMeters);

    return 0.001 * glm::sqrt(glm::abs(schwarzschild * difference)) * falloff;
}