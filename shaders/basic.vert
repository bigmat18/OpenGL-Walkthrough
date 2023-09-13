#version 330 core 
layout (location = 0) in vec3 aPosition; 
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

#define NR_POINT_LIGHTS 2

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpaces[NR_POINT_LIGHTS];
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrixs[NR_POINT_LIGHTS];

void main(void) { 
    gl_Position = projection * view * model * vec4(aPosition, 1.0);

    vs_out.FragPos = vec3(model * vec4(aPosition, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    for (int i = 0; i < NR_POINT_LIGHTS; i++) 
        vs_out.FragPosLightSpaces[i] = lightSpaceMatrixs[i] * vec4(vs_out.FragPos, 1.0);
}