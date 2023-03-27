#version 330 core 
layout (location = 0) in vec3 aPosition; 
layout (location = 1) in vec2 aTexCoord;
// layout (location = 1) in vec3 aColor; 
out vec3 vColor; 
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(void) { 
    gl_Position = projection * view * model * vec4(aPosition, 1.0); 
    vColor = vec3(1.0, 0.0, 0.0);
    TexCoord = aTexCoord;
}