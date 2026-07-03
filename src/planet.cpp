#include "planet.h"
#include "render.h"

planet::planet(glm::vec3 spawnedLocation, float spawnRadius, float spawnMass) : location(spawnedLocation), radius(spawnRadius), mass(spawnMass)
{
    mesh.initialize(radius, location, 128);
    mesh.createMesh();
}

void planet::render()
{
    mesh.render();
}