#version 450 core
layout (location = 0) in vec2 aPos;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * model * vec4(aPos.x, aPos.y, 0.0f, 1.0);
}