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
    //jupiter
    celestialBody jupiter(glm::vec3(0.0f, 0.0f, 0.0f), 0.069911f, 318.0f);

    celestialBody ganymede(glm::vec3(1.07f, 0.0f, 0.0f), 0.00263f);
    celestialBody callisto(glm::vec3(1.883f, 0.0f, 0.0f), 0.00241f);
    celestialBody io(glm::vec3(0.42f, 0.0f, 0.0f), 0.00185f, (1.0f / 66.0f));
    celestialBody europa(glm::vec3(0.671f, 0.0f, 0.0f), 0.0015f);


    sceneObjects.push_back(jupiter);

    //its moons
    ganymede.currentVelocity = glm::vec3(1.0f, 0, -10000.0f);
    sceneObjects.push_back(ganymede);
    sceneObjects.push_back(callisto);
    io.currentVelocity = glm::vec3(0.0f, 0.0f, 5.0f);
    sceneObjects.push_back(io);
    sceneObjects.push_back(europa);
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
            
            primaryBodyRef.currentVelocity = primaryBodyRef.currentVelocity + (calculateGravitationalAcceleration(secondaryBodyRef.mass, distanceBetweenTwoBodies)) * (secondaryBodyRef.location - primaryBodyRef.location);
            secondaryBodyRef.currentVelocity = secondaryBodyRef.currentVelocity + (calculateGravitationalAcceleration(primaryBodyRef.mass, distanceBetweenTwoBodies)) * (primaryBodyRef.location - secondaryBodyRef.location);

            std::cout << "secondary body -> [" << secondaryBodyRef.currentVelocity.x << "] primary body" << std::endl;
        }
    }



    //renders all celestialBodies.
    for (celestialBody body : sceneObjects)
    {
        body.render();
    }
}