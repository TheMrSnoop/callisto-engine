#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "planet.h"

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "windddow", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "could not load opengl" << std::endl;
        glfwTerminate();
        return -1;
    } 

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    std::vector<planet> scenePlanets;
    scenePlanets.push_back(planet(glm::vec3(0.0f, 1.0f, 0.0f)));
    scenePlanets.push_back(planet(glm::vec3(1.0f, 1.0f, 0.0f)));
    scenePlanets.push_back(planet(glm::vec3(2.0f, 1.0f, 0.0f)));


    //VAO object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    //RENDER LOOP
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
    
        for (planet planetInstance : scenePlanets)
        {
            planetInstance.render();
        }


        glfwSwapBuffers(window);
    }

    std::cout << "hello world" << std::endl;
    glfwTerminate();
    return 0;
}