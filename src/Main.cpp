#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sstream>
#include <string>

#include "../libs/Cube.h"
#include "../libs/debugging.h"
#include "../libs/Camera.h"
#include "../libs/Texture2D.h"
#include "../libs/Shader.h"
#include "../libs/FrameBuffer.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera *camera = new Camera(SCR_WIDTH, SCR_HEIGHT, 45.0f);
VertexArray *cubeVAO, *quadVAO, *surfaceVAO;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
glm::vec3 lightPos[] = {
    glm::vec3(-2.0f, 4.0f, -1.0f),
    glm::vec3(5.0f, 3.0f, -1.0f),
};

void renderSchene(Shader *shader);
void MouseCallBackWrapper(GLFWwindow *window, double xpos, double ypos);
void ScrollCallBackWrapper(GLFWwindow *window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);


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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, MouseCallBackWrapper);
    glfwSetScrollCallback(window, ScrollCallBackWrapper);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glewInit();

    glEnable(GL_DEPTH_TEST);
    printout_opengl_glsl_info();

    float vertices[] = {
        // back face
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // bottom-right
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  // top-left
        // front face
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
        // left face
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top-left
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
                                                            // right face
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // top-right
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    // bottom-left
        // bottom face
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
        1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // top-left
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
        -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
        // top face
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
        1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // top-right
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f   // bottom-left
    };

    float surfaces[] = {
        // positions            // normals         // texcoords
        25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
        -25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,

        25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
        -25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,
        25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 25.0f
    };

    float quadVertices[] = {
        // positions        // texture Coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };


    Shader *simpleDepthShader = new Shader("../shaders/shadow_mapping_depth.vert", "../shaders/shadow_mapping_depth.frag");
    Shader *shader = new Shader("../shaders/basic.vert", "../shaders/basic.frag");
    Shader *light = new Shader("../shaders/light.vert", "../shaders/light.frag");

    VertexBuffer *cubeVBO = new VertexBuffer(vertices, 8 * 36 * sizeof(float)),
                 *surfaceVBO = new VertexBuffer(surfaces, 8 * 6 * sizeof(float)),
                 *quadVBO = new VertexBuffer(quadVertices, 20 * sizeof(float));

    cubeVAO = new VertexArray();
    quadVAO = new VertexArray();
    surfaceVAO = new VertexArray();

    VertexBufferLayout *layout = new VertexBufferLayout();
    layout->Push<float>(3);
    layout->Push<float>(3);
    layout->Push<float>(2);

    cubeVAO->AddBuffer(*cubeVBO, *layout);
    surfaceVAO->AddBuffer(*surfaceVBO, *layout);
    quadVAO->AddBuffer(*quadVBO, *layout);

    Texture2D *wood = new Texture2D("wood.png");
    Texture2D *container1 = new Texture2D("container2.png");
    Texture2D *container2 = new Texture2D("container2_specular.png");

    FrameBuffer *frame1 = new FrameBuffer();
    FrameBuffer *frame2 = new FrameBuffer();

    float near_plane = 1.0f, far_plane = 7.5f;

    while (!glfwWindowShouldClose(window)){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera->ProcessInput(window, deltaTime);

        lightPos[0] = glm::vec3(glm::sin(glfwGetTime()) * 2.0f, 4.0f, glm::cos(glfwGetTime()) * 2.0f);
        lightPos[1] = glm::vec3(glm::sin(glfwGetTime()) * -3.0f, 2.0f, glm::cos(glfwGetTime()) * 1.0f);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();

        // 1. render depth of scene to texture (from light's perspective)
        // --------------------------------------------------------------
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        glm::mat4 lightView1 = glm::lookAt(lightPos[0], glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightSpaceMatrix1 = lightProjection * lightView1;

        // render scene from light's point of view
        simpleDepthShader->use();

        simpleDepthShader->setMatrix4("lightSpaceMatrix", lightSpaceMatrix1);
        frame1->BindFrame(window);
        renderSchene(simpleDepthShader);
        frame1->UnbindFrame();

        glm::mat4 lightView2 = glm::lookAt(lightPos[1], glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightSpaceMatrix2 = lightProjection * lightView2;
        simpleDepthShader->setMatrix4("lightSpaceMatrix", lightSpaceMatrix2);
        frame2->BindFrame(window);
        glm::mat4 model = glm::mat4(1.0f);
        simpleDepthShader->setMatrix4("model", model);
        surfaceVAO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        renderSchene(simpleDepthShader);
        frame2->UnbindFrame();

        // 2. render scene as normal using the generated depth/shadow map
        // --------------------------------------------------------------
        shader->use();
        shader->setMatrix4("projection", projection);
        shader->setMatrix4("view", view);

        shader->setFloat("material.shininess", 32.0f);
        shader->setInt("material.diffuse", 0);
        shader->setInt("material.specular", 1);
        shader->setInt("shadowMap1", 2);
        shader->setInt("shadowMap2", 3);

        // directional light
        shader->setVec3("dirLight.direction", (glm::vec3){-0.2f, -1.0f, -0.3f});
        shader->setVec3("dirLight.ambient", (glm::vec3){0.05f, 0.05f, 0.05f});
        shader->setVec3("dirLight.diffuse", (glm::vec3){0.4f, 0.4f, 0.4f});
        shader->setVec3("dirLight.specular", (glm::vec3){0.5f, 0.5f, 0.5f});

        // point light
        for (int i = 0; i < 2; i++) {
            shader->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].position"), lightPos[i]);
            shader->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].ambient"), (glm::vec3){0.05f, 0.05f, 0.05f});
            shader->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].diffuse"), (glm::vec3){0.8f, 0.8f, 0.8f});
            shader->setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].specular"), (glm::vec3){1.0f, 1.0f, 1.0f});
            shader->setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].constant"), 1.0f);
            shader->setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].linear"), 0.09f);
            shader->setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].quadratic"), 0.032f);
        }

        // set light uniforms
        shader->setVec3("viewPos", camera->GetPosition());

        shader->setMatrix4(std::string("lightSpaceMatrixs[") + std::to_string(0) + std::string("]"), lightSpaceMatrix1);
        shader->setMatrix4(std::string("lightSpaceMatrixs[") + std::to_string(1) + std::string("]"), lightSpaceMatrix2);
        
        wood->Bind(0);
        wood->Bind(1);
        frame1->BindTex(2);
        frame2->BindTex(3);

        model = glm::mat4(1.0f);
        shader->setMatrix4("model", model);
        surfaceVAO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        container1->Bind(0);
        container2->Bind(1);
        frame1->BindTex(2);
        frame2->BindTex(3);
        renderSchene(shader);

        light->use();
        light->setMatrix4("projection", projection);
        light->setMatrix4("view", view);

        for(int i = 0; i < 2; i++){
            glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPos[i]);
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
            light->setMatrix4("model", model);
            cubeVAO->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }

        // render Depth map to quad for visual debugging
        // ---------------------------------------------
        // debugDepthQuad->use();
        // debugDepthQuad->setFloat("near_plane", near_plane);
        // debugDepthQuad->setFloat("far_plane", far_plane);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, depthMap);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void renderSchene(Shader *shader) {
    // floor
    glm::mat4 model = glm::mat4(1.0f);
    
    // cubes
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->setMatrix4("model", model);
    cubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->setMatrix4("model", model);
    cubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.25));
    shader->setMatrix4("model", model);
    cubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void MouseCallBackWrapper(GLFWwindow *window, double xpos, double ypos){
    if (camera)
        return camera->MouseCallBack(xpos, ypos);
}

void ScrollCallBackWrapper(GLFWwindow *window, double xoffset, double yoffset){
    if (camera)
        return camera->ScrollCallBack(yoffset);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}