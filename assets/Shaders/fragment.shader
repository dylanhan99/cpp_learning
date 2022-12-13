#version 330 core

out vec4 FragColor;
in vec4 v_Col;

void main()
{
    FragColor = v_Col;
}