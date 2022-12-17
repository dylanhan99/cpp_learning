#version 460 core

in vec4 vCol;
in float vTexSlot;
in vec2 vTexCoord;

out vec4 oCol;

uniform sampler2D uTextures[32];

void main()
{
    int index = int(vTexSlot);
    vec4 mTexColor = texture(uTextures[index], vTexCoord);
    oCol = mTexColor * vec4(vCol.r, vCol.g, vCol.b, vCol.a);

    //oCol = vec4(vTexSlot, vTexSlot, vTexSlot, vTexSlot);

    //oCol = vec4(vCol.r, vCol.g, vCol.b, vCol.a);
    //oCol = vec4(1.0f, 0.5f, 0.2f, 1.0f);

}