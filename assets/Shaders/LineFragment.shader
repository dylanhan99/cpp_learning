#version 460 core

in vec4 vCol;

out vec4 oCol;

void main()
{
    oCol = vec4(vCol.r, vCol.g, vCol.b, vCol.a);
}