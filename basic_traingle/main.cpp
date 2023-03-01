#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "debugging.h"

const char *vertexShaderSRC = "#version 330 core\n"
                              "layout (location = 0) in vec3 aPos;\n"
                              "layout (location = 1) in vec3 aColor;\n"
                              "out vec3 vColor;\n"
                              "void main()\n"
                              "{\n"
                              "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                              "   vColor = aColor;\n"
                              "}\0";

const char *fragmentShaderSRC = "#version 330 core\n"
                                "in vec3 vColor;\n"
                                "out vec4 FragColor;\n"
                                "void main()\n"
                                "{\n"
                                "   FragColor = vec4(vColor, 1.0f);\n"
                                "}\n\0";

int main(void) {
    if(!glfwInit()) 
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow *window = glfwCreateWindow(1000, 800, "Test", NULL, NULL);
    if(!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    GLuint posIndex = 0, colorIndex = 1;

    GLfloat vertices[] = {
        0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f  // top left
    };

    GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    check_gl_errors(__LINE__, __FILE__);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    check_gl_errors(__LINE__, __FILE__);

    glVertexAttribPointer(posIndex, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), GL_NONE);
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    check_gl_errors(__LINE__, __FILE__);

    glEnableVertexAttribArray(posIndex);
    glEnableVertexAttribArray(colorIndex);
    check_gl_errors(__LINE__, __FILE__);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSRC, GL_NONE);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSRC, GL_NONE);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        check_gl_errors(__LINE__, __FILE__);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        check_gl_errors(__LINE__, __FILE__);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}