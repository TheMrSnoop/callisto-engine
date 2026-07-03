#include "planet.h"
#include "render.h"



moon::moon(float spawnRadius, float distanceFromPlanet, float spawnMass)
{
    distance = distanceFromPlanet; radius = spawnRadius; mass = spawnMass;
}

void moon::orbit()
{
    theta += 0.1f;

    float x = glm::cos(glm::radians(theta)) * distance;
    float y = glm::sin(glm::radians(theta)) * distance;

    mesh.initialize(radius, glm::vec3(x, y, 0.0f), 16, 32);
    mesh.createMesh();
    mesh.render();
}


planet::planet(glm::vec3 spawnedLocation, float spawnRadius, float spawnMass) : location(spawnedLocation), radius(spawnRadius), mass(spawnMass)
{
    mesh.initialize(radius, location * glm::vec3(1.0f, 1.0f, 1.0f), 32, 64);
    mesh.createMesh();
}

void planet::render()
{
    mesh.render();

    //checks on tick. this is bad.
    if (!moons.empty())
    {
        for (moon moonSingle : moons)
        {
            moonSingle.orbit();
        }
    }
}



