#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

int main(){
        glewExperimental = true;
        if(!glfwInit()){
                std::cerr << "Failed to initialise GLFW\n" << std::endl;
                return -1;
        }
        glfwWindowHint(GLFW_SAMPLES,4); //antialiasing 4x
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window;
        window = glfwCreateWindow(400,400,"No Title is going to be set",NULL,NULL);

        glfwMakeContextCurrent(window);
        return 0;
}



