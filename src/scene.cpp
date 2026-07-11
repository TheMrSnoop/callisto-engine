#include "scene.h"
#include "celestialBody.h"

//MODIFIED/SIMPLIFIED because mass is in terms of (mass of the earth)x
long gravitationalConstant = 2.3805e39L;

float scene::calculateGravitationalAcceleration(float objectMassInXEarth, float distanceSquared)
{
    const long modifiedG = (3.986e14L * 1e-9L);

    // A = (G * mass) / radius^2

    //distance is in gigameters
    float accelerationInMS = (modifiedG * objectMassInXEarth) / distanceSquared;
    
    //1 meter = 1x10^-9 giga meters (radius unit)
    return (accelerationInMS * 1e-9L) * 0.01;

}

scene::scene()
{
    celestialBody earth(glm::vec3(0.0f, 0.0f, 0.0f), 0.00637814f, 1.0f);
    celestialBody moon(glm::vec3(0.384f, 0.0f, 0.0f), 0.0017374f, 0.012f);

    
    celestialBody jupiter(glm::vec3(0.0f, 0.0f, 0.0f), 0.069911f, 318.0f);
    celestialBody saturn(glm::vec3(0.13f, 0.0f, 10.0f), 0.058232f, 95.16f);
    celestialBody uranus(glm::vec3((0.13f + 0.025f + 0.0582f), 0.0f, 10.0f), 0.025362f, 14.5f);
    celestialBody neptune(glm::vec3((0.13f + 0.025f + 0.0582f + 0.0246f), 0.0f, 10.0f), 0.024622f, 17.15f);



    celestialBody ganymede(glm::vec3(1.07f, 0.0f, 0.0f), 0.00263f);
    celestialBody callisto(glm::vec3(1.883f, 0.0f, 0.0f), 0.00241f);
    celestialBody io(glm::vec3(0.42f, 0.0f, 0.0f), 0.00185f, (1.0f / 66.0f));
    celestialBody europa(glm::vec3(0.671f, 0.0f, 0.0f), 0.0015f);


    sceneObjects.push_back(jupiter);
    //sceneObjects.push_back(saturn);
    //sceneObjects.push_back(uranus);
    //sceneObjects.push_back(neptune);

    //its moons
    ganymede.currentVelocity = glm::vec3(0.0f, 0, 0.1f);
    sceneObjects.push_back(ganymede);
    //sceneObjects.push_back(callisto);
    io.currentVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
    sceneObjects.push_back(io);
    //sceneObjects.push_back(europa);

    //sceneObjects.push_back(earth);
    //sceneObjects.push_back(moon);
}

void scene::renderScene()
{
    float time = glfwGetTime();
    //F = ma
    //A = F/m (in kg)

    for (int i1 = 0; i1 < sceneObjects.size(); i1++)
    {
        celestialBody& primaryBodyRef = sceneObjects[i1];


        for (int i2 = i1 + 1; i2 < sceneObjects.size(); i2++)
        {
            celestialBody& secondaryBodyRef = sceneObjects[i2];
            
            float distanceBetweenTwoBodies = math::distanceSquared(primaryBodyRef.location, secondaryBodyRef.location);
            
            primaryBodyRef.currentVelocity = primaryBodyRef.currentVelocity + (calculateGravitationalAcceleration(secondaryBodyRef.mass, distanceBetweenTwoBodies)) * (glm::normalize(secondaryBodyRef.location - primaryBodyRef.location));
            secondaryBodyRef.currentVelocity = secondaryBodyRef.currentVelocity + (calculateGravitationalAcceleration(primaryBodyRef.mass, distanceBetweenTwoBodies)) * (glm::normalize(primaryBodyRef.location - secondaryBodyRef.location));
        }
    }



    //renders all celestialBodies.
    for (celestialBody body : sceneObjects)
    {
        body.render();
    }


    grid newGrid;
    newGrid.initialize(sceneObjects, 8);
    newGrid.render();

}