#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.h"
#include "planet.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned short resX = 2560;
unsigned short resY = 1440;

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

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
    scenePlanets.push_back(planet(glm::vec3(-2.5f, 0.0f, 0.0f)));


    //VAO object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    //create and compile shaders
	shader meshShader;
	GLuint programID = meshShader.createShader("/home/thomas/callisto-engine/shaders/default.vert", "/home/thomas/callisto-engine/shaders/default.frag");


    GLint viewLoc = glGetUniformLocation(programID, "view");
    GLint projLoc = glGetUniformLocation(programID, "projection");

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<float>(resX) / static_cast<float>(resY) , 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f),  // camera position
        glm::vec3(0.0f, 0.0f, 0.0f),  // look-at target
        glm::vec3(0.0f, 1.0f, 0.0f)   // up vector
    );


    //RENDER LOOP
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
    
        glUseProgram(programID);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        for (planet planetInstance : scenePlanets)
        {
            planetInstance.render();
        }


        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}