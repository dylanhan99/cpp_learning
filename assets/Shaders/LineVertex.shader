#version 460 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aCol;

out vec4 vCol;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

void main()
{
    gl_Position = pr_matrix * vw_matrix * ml_matrix * aPosition;

    vCol = aCol;
}