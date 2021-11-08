#version 300 es
precision mediump float; // 중간 정도의 정밀도.

uniform sampler2D uTexCoord;
in vec2 v_TexPos;
out vec4 outColor;

void main()
{
    vec2 texPos = v_TexPos;
    texPos.y = 1.0f - texPos.y;
    outColor = vec4(v_TexPos.x,v_TexPos.y,0.0f,1.0f);
    outColor = texture(uTexCoord, texPos);
}