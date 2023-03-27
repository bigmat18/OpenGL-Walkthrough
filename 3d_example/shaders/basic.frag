#version 330 core  
out vec4 color; 

in vec3 vColor; 
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main(void) { 
    color = texture(ourTexture, TexCoord); 
} 