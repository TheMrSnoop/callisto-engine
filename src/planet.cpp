#include "planet.h"
#include "render.h"

planet::planet(glm::vec3 spawnedLocation, float spawnRadius = 1.0f, float spawnMass = 1.0f)
{
    location = spawnedLocation;
    glPointSize(radius);
}

void planet::render()
{
    circle planetMesh(radius, location, 24);
    planetMesh.render();
}