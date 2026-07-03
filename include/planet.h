#pragma once

#include "dependencies.h"
#include "render.h"


class moon
{
public:
    //constructor
    moon(float spawnRadius, float distanceFromPlanet = 0.01f, float spawnMass = 1.0f);

    void render();

    void orbit();
private:
    //in terms of x(mass of earth)
    float mass;

    //in terms of megameters
    float radius;

    //HSV color
    glm::vec4 color;

    //in gigameters
    float distance;

    //in degrees
    float theta = 0.0f;
    float lastTheta;


    sphere mesh;
};



class planet
{
public:
    //constructor
    planet(glm::vec3 spawnedLocation, float spawnRadius = 0.0637f, float spawnMass = 1.0f);

    void render();

    glm::vec3 getPlanetLocation() { return location; }


    std::vector<moon> moons;
private:
    //in terms of x(mass of earth)
    float mass;

    //in terms of megameters
    float radius;

    //HSV color
    glm::vec4 color;

    //current world space coordinates
    glm::vec3 location;

    sphere mesh;
};


