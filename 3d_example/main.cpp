#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../utils/debugging.h"
#include "../utils/Shader.h"
#include "../utils/Renderer.h"

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

    GLuint posIndex = 0, colorIndex = 1;

    GLfloat vertices[] = {
        -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f, 0.5f, 0.5f,
        1.0f, 1.0f, -1.0f, 0.5f, 1.0f, 0.5f
    };

    GLuint indices[] = {
        0, 1, 2, 2, 1, 3, // front
        5, 4, 7, 7, 4, 6, // back
        4, 0, 6, 6, 0, 2, // left
        1, 5, 3, 3, 5, 7, // right
        2, 3, 6, 6, 3, 7, // top
        4, 5, 0, 0, 5, 1  // bottom
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(-2.0f, 2.0f, 0.0f),
        glm::vec3(-2.0f, -2.0f, 0.0f),
        glm::vec3(2.0f, 2.0f, 0.0f),
        glm::vec3(2.0f, -2.0f, 0.0f)
    };

    Renderer *renderer = new Renderer();
    
    for(unsigned int i=0; i<4; i++){
        renderer->addVertexColored(vertices, sizeof(vertices), posIndex, colorIndex);
        renderer->addIndeces(indices, sizeof(indices));
    }

    Shader *shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
    glEnable(GL_DEPTH_TEST);


    while (!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();

        for(int i=0; i<4; i++){
            glm::mat4 model = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f)), cubePositions[i]);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection;

            shader->setMatrix4("model", glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)));
            shader->setMatrix4("view", glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)));
            shader->setMatrix4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));

            renderer->bind();
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    

    return 0;
}