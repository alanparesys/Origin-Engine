#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 projection;
uniform mat4 model;

out vec2 TexCoords;
void main() {
    gl_Position = vec4(aPos * 0.0005, 1.0); 
}