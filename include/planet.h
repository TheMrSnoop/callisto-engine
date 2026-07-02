#include "dependencies.h"

class planet
{
public:
    //constructor
    planet(glm::vec3 spawnedLocation, float spawnRadius = 1.0f, float spawnMass = 1.0f);

    void render();

    glm::vec3 getPlanetLocation() { return location; }
private:
    //in terms of x(mass of earth)
    float mass;

    //in terms of x(radius of earth)
    float radius;

    //HSV color
    glm::vec4 color;

    //current world space coordinates
    glm::vec3 location;
};