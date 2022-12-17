#version 460 core

in vec4 vCol;
in float vTexSlot;
in vec2 vTexCoord;

out vec4 oCol;

uniform sampler2D uTextures[32];

void main()
{
    int index = int(vTexSlot);
    if (index >= 0) {
        vec4 mTexColor = texture(uTextures[index], vTexCoord);
        oCol = mTexColor * vec4(vCol.r, vCol.g, vCol.b, vCol.a);
    } else {
        oCol = vec4(vCol.r, vCol.g, vCol.b, vCol.a);
    }

}