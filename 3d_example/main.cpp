#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../utils/debugging.h"
#include "../utils/Shader.h"
#include "../utils/Renderer.h"
#include "../utils/Cube.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    std::vector<GLfloat> colors = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.5f,
        0.0f, 0.5f, 0.5f
    };

    Renderer *renderer = new Renderer();
    Cube *cube = new Cube(colors, 0.5f);

    renderer->addShape(cube);

    Shader *shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f)
    };

    while (!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();

        for(int i=0; i<3; ++i){
            glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection;

            shader->setMatrix4("model", model);
            shader->setMatrix4("view", glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f)));
            shader->setMatrix4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));

            renderer->bind();
            glDrawElements(GL_TRIANGLES, cube->getIndices().size(), GL_UNSIGNED_INT, 0);
        }


        // glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    

    return 0;
}