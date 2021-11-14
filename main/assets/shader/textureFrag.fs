#version 300 es
precision mediump float; // 중간 정도의 정밀도.

uniform sampler2D uTexCoord;
uniform vec3 tintColor;
uniform bool isDrawFont;
in vec2 v_TexPos;
out vec4 outColor;

void main()
{
    vec2 texPos = v_TexPos;
    texPos.y = 1.0f - texPos.y;
    if(!isDrawFont)
    {
        //outColor = vec4(v_TexPos.x,v_TexPos.y,0.0f,1.0f);
        outColor = texture(uTexCoord, texPos);
        vec4 mulTintColor = vec4(tintColor, outColor.a);
        outColor = outColor * mulTintColor;
    }
    else
    {
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTexCoord, v_TexPos).r);
        outColor = vec4(tintColor, 1.0) * sampled;//vec4(1.0f,0.0f,0.0f,1.0f);//
    }
}