#pragma once
#include "dependencies.h"
#include "celestialBody.h"

class scene
{
public:
    scene();
    void renderScene();
    std::vector<celestialBody> sceneObjects;

private:
    float calculateGravitationalAcceleration(float objectMassInXEarth, float radius);

};