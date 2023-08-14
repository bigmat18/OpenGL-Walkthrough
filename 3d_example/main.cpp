#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sstream>
#include <string>

#include "../framework/Cube.h"
#include "../framework/debugging.h"
#include "../framework/Camera.h"
#include "../framework/Texture.h"
#include "../framework/Shader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera *camera = new Camera(SCR_WIDTH, SCR_HEIGHT, 45);
float deltaTime = 0.0f;
float lastFrame = 0.0f;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void MouseCallBackWrapper(GLFWwindow *window, double xpos, double ypos){
    if (camera)
        return camera->MouseCallBack(xpos, ypos);
}

void ScrollCallBackWrapper(GLFWwindow *window, double xoffset, double yoffset){
    if (camera)
        return camera->ScrollCallBack(yoffset);
}

int main(void){
    if(!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D test", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();
    printout_opengl_glsl_info();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    float surfaces[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    };

    Texture *container = new Texture("container2.png");
    Texture *container_specular = new Texture("container2_specular.png");
    Texture *wood = new Texture("wood.png");

    Shader *cube = new Shader("shaders/basic.vert", "shaders/basic.frag");
    Shader *light = new Shader("shaders/light.vert", "shaders/light.frag");
    Shader *surface = new Shader("shaders/surface.vert", "shaders/surface.frag");

    VertexBuffer *VBO = new VertexBuffer(vertices, 8 * 36 * sizeof(float)),
                 *surfaceVBO = new VertexBuffer(surfaces, 8 * 6 * sizeof(float));

    VertexArray *cubeVAO = new VertexArray(), 
                *lightcubeVAO = new VertexArray(),
                *surfaceVAO = new VertexArray();

    VertexBufferLayout *layout = new VertexBufferLayout();
    layout->Push<float>(3);
    layout->Push<float>(3);
    layout->Push<float>(2);

    VertexBufferLayout *layoutSourface = new VertexBufferLayout();
    layoutSourface->Push<float>(3);
    layoutSourface->Push<float>(3);
    layoutSourface->Push<float>(2);

    cubeVAO->AddBuffer(*VBO, *layout);
    lightcubeVAO->AddBuffer(*VBO, *layout);
    surfaceVAO->AddBuffer(*surfaceVBO, *layoutSourface);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        // glm::vec3( 2.0f,  5.0f, -15.0f), 
        // glm::vec3(-1.5f, -2.2f, -2.5f),  
        // glm::vec3(-3.8f, -2.0f, -12.3f),  
        // glm::vec3( 2.4f, -0.4f, -3.5f),  
        // glm::vec3(-1.7f,  3.0f, -7.5f),  
        // glm::vec3( 1.3f, -2.0f, -2.5f),  
        // glm::vec3( 1.5f,  2.0f, -2.5f), 
        // glm::vec3( 1.5f,  0.2f, -1.5f), 
        // glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( -1.8f, 0.1f, -2.4f),
        // glm::vec3(-4.0f,  2.0f, -12.0f),
        // glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::mat4 model, projection, view;

    while (!glfwWindowShouldClose(window)){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera->ProcessInput(window, deltaTime);
        glfwSetCursorPosCallback(window, MouseCallBackWrapper);
        glfwSetScrollCallback(window, ScrollCallBackWrapper);

        projection = glm::perspective(glm::radians(camera->GetZoom()), 800.0f / 600.0f, 0.1f, 100.0f);
        view = camera->GetViewMatrix();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
        model = glm::scale(model, glm::vec3(7.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        cube->use();
        cube->setMatrix4("model", model);
        cube->setMatrix4("view", view);
        cube->setMatrix4("projection", projection);
        cube->setVec3("viewPos", camera->GetPosizion());
        cube->setInt("material.diffuse", 1);
        cube->setInt("material.specular", 1);
        cube->setFloat("material.shininess", 32.0f);

        cube->setVec3("light.diraction", (glm::vec3){-0.2f, -1.0f, -0.3f});
        cube->setVec3("light.ambient", (glm::vec3){0.05f, 0.05f, 0.05f});
        cube->setVec3("light.diffuse", (glm::vec3){0.4f, 0.4f, 0.4f});
        cube->setVec3("light.specular", (glm::vec3){0.5f, 0.5f, 0.5f});

        for (unsigned int i = 0; i < 2; i++) {
            cube->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].position"), pointLightPositions[i]);
            cube->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].ambient"), (glm::vec3){0.05f, 0.05f, 0.05f});
            cube->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].diffuse"), (glm::vec3){0.8f, 0.8f, 0.8f});
            cube->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].specular"), (glm::vec3){1.0f, 1.0f, 1.0f});
            cube->setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].constant"), 1.0f);
            cube->setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].linear"), 0.09f);
            cube->setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].quadratic"), 0.032f);
        }
        wood->Bind(1);
        surfaceVAO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        light->use();
        light->setMatrix4("view", view);
        light->setMatrix4("projection", projection);

        for (unsigned int i = 0; i < 2; i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            light->setMatrix4("model", model);
            lightcubeVAO->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        for (unsigned int i = 0; i < 1; i++){
            cube->use();
            cube->setMatrix4("view", view);
            cube->setMatrix4("projection", projection);
            cube->setVec3("viewPos", camera->GetPosizion());
            cube->setInt("material.diffuse", 0);
            cube->setInt("material.specular", 1);
            cube->setFloat("material.shininess", 32.0f);

            cube->setVec3("light.diraction", (glm::vec3){-0.2f, -1.0f, -0.3f});
            cube->setVec3("light.ambient", (glm::vec3){0.05f, 0.05f, 0.05f});
            cube->setVec3("light.diffuse", (glm::vec3){0.4f, 0.4f, 0.4f});
            cube->setVec3("light.specular", (glm::vec3){0.5f, 0.5f, 0.5f});

            for (unsigned int i = 0; i < 2; i++) {
                cube->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].position"), pointLightPositions[i]);
                cube->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].ambient"), (glm::vec3){0.05f, 0.05f, 0.05f});
                cube->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].diffuse"), (glm::vec3){0.8f, 0.8f, 0.8f});
                cube->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].specular"), (glm::vec3){1.0f, 1.0f, 1.0f});
                cube->setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].constant"), 1.0f);
                cube->setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].linear"), 0.09f);
                cube->setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].quadratic"), 0.032f);
            }

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            cube->setMatrix4("model", model);

            wood->Bind(0);
            // container_specular->Bind(1);
            cubeVAO->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    delete VBO;
    delete cubeVAO;
    delete lightcubeVAO;
    delete cube;
    delete light;
    delete layout;
    delete container;
    delete container_specular;

    glfwTerminate();
    
    return 0;
}