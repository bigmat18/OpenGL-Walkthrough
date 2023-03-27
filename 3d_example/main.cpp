#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../framework/Cube.h"
#include "../framework/debugging.h"
#include "../framework/Camera.h"

Camera *camera = new Camera(800, 600, 45);

void MouseCallBackWrapper(GLFWwindow *window, double xpos, double ypos){
    if (camera)
        return camera->MouseCallBack(window, xpos, ypos);
}

void ScrollCallBackWrapper(GLFWwindow *window, double xoffset, double yoffset){
    if (camera)
        return camera->ScrollCallBack(window, xoffset, yoffset);
}

int main(void){
    if(!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "3D test", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();
    printout_opengl_glsl_info();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // std::vector<GLfloat> colors = {
    //     1.0f, 0.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f,
    //     0.0f, 0.0f, 1.0f,
    //     1.0f, 0.0f, 1.0f,
    //     0.0f, 1.0f, 1.0f,
    //     1.0f, 1.0f, 0.0f,
    //     0.5f, 0.0f, 0.5f,
    //     0.0f, 0.5f, 0.5f
    // };

    Cube* cube = new Cube(0.5f, "shaders/basic.vert", "shaders/basic.frag");
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->UpdateDeltaTime();
        camera->ProcessInput(window);
        glfwSetCursorPosCallback(window, MouseCallBackWrapper);
        glfwSetScrollCallback(window, ScrollCallBackWrapper);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        glm::mat4 projection = glm::perspective(glm::radians(camera->GetFov()), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix(window);

        cube->setShaderUniform<glm::mat4>(model, "model");
        cube->setShaderUniform<glm::mat4>(view, "view");
        cube->setShaderUniform<glm::mat4>(projection, "projection");

        cube->Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}