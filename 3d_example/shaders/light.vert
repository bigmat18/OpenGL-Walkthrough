#version 330 core 
layout (location = 0) in vec3 aPosition; 
layout (location = 1) in vec3 Normals; 
layout (location = 2) in vec3 TexCoords; 

out vec4 fragColor; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(void) { 
    gl_Position = projection * view * model * vec4(aPosition, 1.0); 
    fragColor = vec4(1.0);
}