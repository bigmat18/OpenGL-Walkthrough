#version 330 core 
layout (location = 0) in vec3 aPosition; 
// layout (location = 1) in vec3 aColor; 
out vec3 vColor; 

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;


void main(void) { 
    gl_Position = vec4(aPosition, 1.0); 
    vColor = vec3(1.0, 0.0, 0.0);
}