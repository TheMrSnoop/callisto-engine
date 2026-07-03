#include "camera.h"
#include "system.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>


unsigned int width = installationSettings::renderWidth;
unsigned int height = installationSettings::renderHeight;







// the static bridge function GLFW calls
void camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Retrieve the pointer to the camera instance from the GLFW window
    camera* cam = static_cast<camera*>(glfwGetWindowUserPointer(window));
    
    if (cam)
    {
        // calls this
        cam->mouseScroll(yoffset);
    }
}



void camera::mouseScroll(double yoffset)
{
    float modifier = lastSpeedMultiplier + (yoffset * 0.05);
    if (modifier >= 0.01f && modifier <= 100.0f)
    {
        speedMultiplier = modifier;
        lastSpeedMultiplier = speedMultiplier;
        std::cout << "new speed multiplier:" << speedMultiplier << std::endl;
    }

}

void camera::checkInput(GLFWwindow* windowRef)
{
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();

    if (glfwGetMouseButton(windowRef, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
		//Hides the cursor
		glfwSetInputMode(windowRef, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


		//Prevents the camera from jumping around on the first click
		if (firstClick)
		{
			//Resets the cursor to the center of the screen. /2 because that is 50%.
			glfwSetCursorPos(windowRef, (width / 2), (height / 2));
			firstClick = false;
		}

        //mouse scroll





        //WASD
        if (glfwGetKey(windowRef, GLFW_KEY_W) == GLFW_PRESS)
        {
            location += deltaTime * speed * speedMultiplier * orientation;
        }
        if (glfwGetKey(windowRef, GLFW_KEY_A) == GLFW_PRESS)
        {
            location += speed * speedMultiplier * deltaTime * -glm::normalize(glm::cross(orientation, up));
        }

        if (glfwGetKey(windowRef, GLFW_KEY_S) == GLFW_PRESS)
        {
            location += speed * speedMultiplier * deltaTime * -orientation;
        }

        if (glfwGetKey(windowRef, GLFW_KEY_D) == GLFW_PRESS)
        {
            location += speed * speedMultiplier * deltaTime * glm::normalize(glm::cross(orientation, up));
        }





        //MOUSE CONTROLS
        if (glfwGetMouseButton(windowRef, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            double mouseX;
            double mouseY;
            glfwGetCursorPos(windowRef, &mouseX, &mouseY);


            float rotX = sensitivity * (float)(mouseY - (height / 2)) / (float)height;
            float rotY = sensitivity * (float)(mouseX - (width / 2)) / (float)width;

    

            glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

            //Makes sure that you cannot do barrel rolls and flip upside down before applying the new Orientation
            if (!(glm::angle(newOrientation, up) <= glm::radians(5.0f) or glm::angle(newOrientation, -up) <= glm::radians(5.0f))) orientation = newOrientation;
            


            orientation = glm::rotate(orientation, glm::radians(-rotY), up);

            //Resets the cursor to the center of the screen. /2 because that is 50%.
            glfwSetCursorPos(windowRef, (width / 2), (height / 2));
        }



        //OTHER CONTROLS
        if (glfwGetKey(windowRef, GLFW_KEY_SPACE) == GLFW_PRESS or glfwGetKey(windowRef, GLFW_KEY_E) == GLFW_PRESS)
        {
            location += speed * speedMultiplier * deltaTime * up;
        }

        if (glfwGetKey(windowRef, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS or glfwGetKey(windowRef, GLFW_KEY_Q) == GLFW_PRESS)
        {
            location += speed * speedMultiplier * deltaTime * -up;
        }


    }
	else if (glfwGetMouseButton(windowRef, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		glfwSetInputMode(windowRef, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}





}