#version 460 core

in vec4 vCol;
in vec2 vTexCoord;

out vec4 oCol;

uniform sampler2D uTextures;

void main()
{
    //o_Col = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //oCol = vec4(vCol.r, vCol.g, vCol.b, vCol.a);
    vec4 mTexColor = texture(uTextures, vTexCoord);
    oCol = mTexColor * vec4(vCol.r, vCol.g, vCol.b, vCol.a);
}