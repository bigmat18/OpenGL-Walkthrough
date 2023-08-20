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
#include "../framework/FrameBuffer.h"

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


    Shader *simpleDepthShader = new Shader("shaders/shadow_mapping_depth.vert", "shaders/shadow_mapping_depth.frag");
    Shader *debugDepthQuad = new Shader("shaders/debug_quad.vert", "shaders/debug_quad_depth.frag");
    Shader *shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
    Shader *light = new Shader("shaders/light.vert", "shaders/light.frag");

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

    Texture *wood = new Texture("wood.png");
    Texture *container1 = new Texture("container2.png");
    Texture *container2 = new Texture("container2_specular.png");

    FrameBuffer *frame = new FrameBuffer();

    float near_plane = 1.0f, far_plane = 7.5f;

    // debugDepthQuad->use();
    // debugDepthQuad->setInt("depthMap", 0);

    while (!glfwWindowShouldClose(window)){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera->ProcessInput(window, deltaTime);


        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();

        // 1. render depth of scene to texture (from light's perspective)
        // --------------------------------------------------------------
        std::vector<glm::mat4> lightSpaceMatrixs;
        for(int i = 0; i < 1; i++) {
            glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
            // glm::mat4 lightProjection = glm::perspective<float>(glm::radians(45.0f), 1.0f, 2.0f, 50.0f);
            glm::mat4 lightView = glm::lookAt(lightPos[i], glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
            glm::mat4 lightSpaceMatrix = lightProjection * lightView;
            lightSpaceMatrixs.push_back(lightSpaceMatrix);

            // render scene from light's point of view
            simpleDepthShader->use();
            simpleDepthShader->setMatrix4("lightSpaceMatrix", lightSpaceMatrix);

            frame->BindFrame(window);
            renderSchene(simpleDepthShader);
            frame->UnbindFrame();
        }

        // 2. render scene as normal using the generated depth/shadow map
        // --------------------------------------------------------------
        shader->use();
        shader->setMatrix4("projection", projection);
        shader->setMatrix4("view", view);

        shader->setFloat("material.shininess", 32.0f);
        shader->setInt("shadowMap", 2);
        shader->setInt("material.diffuse", 0);
        shader->setInt("material.specular", 1);

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

        for(int i = 0; i<lightSpaceMatrixs.size(); i++)
            shader->setMatrix4(std::string("lightSpaceMatrixs[") + std::to_string(i) + std::string("]"), lightSpaceMatrixs[i]);
        container1->Bind(0);
        container2->Bind(1);
        frame->BindTex(2);
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
    shader->setMatrix4("model", model);
    surfaceVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
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