#version 460 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aCol;
layout(location = 2) in vec2 aTexCoord;

out vec4 vCol;
out vec2 vTexCoord;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

void main()
{
    gl_Position = pr_matrix * vw_matrix * ml_matrix * aPosition;
    //gl_Position = aPosition;
    
    vCol = aCol;
    vTexCoord = aTexCoord;
}