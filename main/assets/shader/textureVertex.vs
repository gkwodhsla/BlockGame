#version 300 es

in vec4 position;
in vec2 inputTexPos;
out vec2 v_TexPos;

uniform mat4 worldTrans;
uniform mat4 cameraTrans;
uniform mat4 projTrans;
uniform bool isDrawFont;
void main()
{

        mat4 MVP = projTrans*cameraTrans*worldTrans;
        vec4 outPos = MVP*position;
        gl_Position = outPos;
        v_TexPos = inputTexPos;

}