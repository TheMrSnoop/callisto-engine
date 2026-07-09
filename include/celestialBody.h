#pragma once

#include "dependencies.h"
#include "render.h"


class celestialBody
{
public:
    //constructor
    celestialBody(glm::vec3 spawnedLocation, float spawnRadius = 0.0637f, float spawnMass = 1.0f);

    void render();

    //in terms of x(mass of earth)
    float mass;

    //in terms of gigameters
    float radius;

    //current world space coordinates
    glm::vec3 location;
    glm::vec3 currentVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
private:
    

    //HSV color
    glm::vec4 color;

    sphere mesh;
};


