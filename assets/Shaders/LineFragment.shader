#version 460 core

out vec4 o_Col;
in vec4 v_Col;

void main()
{
    //o_Col = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    o_Col = vec4(v_Col.r, v_Col.g, v_Col.b, v_Col.a);
}