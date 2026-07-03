#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.h"
#include "planet.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "system.h"
#include "star.h"



int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    unsigned int resX = installationSettings::renderWidth;
    unsigned int resY = installationSettings::renderHeight;

    window = glfwCreateWindow(resX, resY, "Callisto Engine", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "could not load opengl" << std::endl;
        glfwTerminate();
        return -1;
    } 

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // a single planet for now.
    std::vector<planet> scenePlanets;
    //earth
    //scenePlanets.push_back(planet(glm::vec3(150.0f, 0.0f, 0.0f)));

    //jupiter
    planet jupiter(glm::vec3(0.0f, 0.0f, 0.0f), 0.069911f);
    
    moon ganymede(0.00263f);
    moon callisto(0.00241f);
    moon io(0.001821f);
    moon europa(0.00156f);
    jupiter.moons.push_back(ganymede);
    jupiter.moons.push_back(callisto);
    jupiter.moons.push_back(io);
    jupiter.moons.push_back(europa);

    scenePlanets.push_back(jupiter);


    star sun(0.697f);
    


    //VAO object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    //create and compile shaders
	shader meshShader;
	GLuint programID = meshShader.createShader("/home/thomas/callisto-engine/shaders/default.vert", "/home/thomas/callisto-engine/shaders/default.frag");


    GLint viewLoc = glGetUniformLocation(programID, "view");
    GLint projLoc = glGetUniformLocation(programID, "projection");

    //TODO: projection stuff should be moved to camera
    float nearPlane = 0.01f;
    float farPlane = 10000000.0f; 
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<float>(resX) / static_cast<float>(resY) , nearPlane, farPlane);

    camera mainCamera;
    mainCamera.speed = 8.0f;
    mainCamera.sensitivity = 250.0f;

    // gives GLFW a pointer to the camera object instance
    glfwSetWindowUserPointer(window, &mainCamera);

    // registers the static camera callback function
    glfwSetScrollCallback(window, camera::scroll_callback);



    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //RENDER LOOP
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        mainCamera.checkInput(window);


        glm::mat4 view = glm::lookAt(
            mainCamera.location,  // camera position
            mainCamera.location + mainCamera.orientation,  // look-at target
            mainCamera.up   // up vector
        );
    
        glUseProgram(programID);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        //sun.render();

        for (planet planetInstance : scenePlanets)
        {
            planetInstance.render();
        }




        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}