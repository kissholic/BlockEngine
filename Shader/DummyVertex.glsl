#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;
uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}