#pragma once
#include "dependencies.h"

class camera
{
public:
    void checkInput(GLFWwindow* windowRef);
    void mouseScroll(double yoffset);


    // static bridge function that GLFW will call
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    glm::vec3 location;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float speed;
    float sensitivity;
private:
    float deltaTime;
    float lastTime;
    bool firstClick = true;
    float speedMultiplier = 1.0f;
    float lastSpeedMultiplier;
};