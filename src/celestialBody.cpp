#include "celestialBody.h"
#include "render.h"

using namespace std;


celestialBody::celestialBody(glm::vec3 spawnedLocation, float spawnRadius, float spawnMass) : location(spawnedLocation), radius(spawnRadius), mass(spawnMass)
{
    mesh.initialize(radius, location * glm::vec3(1.0f, 1.0f, 1.0f), 32, 64);
    mesh.createMesh();
}

void celestialBody::render()
{
    float currentTime = glfwGetTime();
    location = location + currentVelocity;

    mesh.initialize(radius, location * glm::vec3(1.0f, 1.0f, 1.0f), 32, 64);
    mesh.createMesh();
    mesh.render();
}

