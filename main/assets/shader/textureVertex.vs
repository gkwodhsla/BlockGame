#version 300 es

in vec4 position;
in vec2 inputTexPos;

//파티클의 인스턴싱 드로우를 위한 속도와 가속도 값
in vec2 vel;
in vec2 acc;

out vec2 v_TexPos;

uniform mat4 worldTrans;
uniform mat4 cameraTrans;
uniform mat4 projTrans;
uniform bool isDrawFont;

uniform bool isInstanceDraw;
uniform float time;


void main()
{
    if(isInstanceDraw)
    {
                //xPos = vel.x * time + 0.5f * acc.x * time * time;
                //yPos = vel.y * time + 0.5f * (acc.y + G_ACCEL) * time * time;
                mat4 transMat = mat4(1.0f, 0.0f, 0.0f, 1.0f,
                                     0.0f, 1.0f, 0.0f, 1.0f,
                                     0.0f, 0.0f, 1.0f, 0.0f,
                                     0.0f, 0.0f, 0.0f, 1.0f);
                transMat = transpose(transMat);
                mat4 MVP = projTrans*cameraTrans*transMat*worldTrans;
                vec4 retVal = MVP*position;
                gl_Position = retVal;
    }
    else
    {
        mat4 MVP = projTrans*cameraTrans*worldTrans;
        vec4 outPos = MVP*position;
        gl_Position = outPos;
    }
    v_TexPos = inputTexPos;
}