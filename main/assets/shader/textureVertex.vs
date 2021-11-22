#version 300 es

in vec4 position;
in vec2 inputTexPos;

in vec2 vel;
in vec2 acc;
in vec2 addPos;
in float lifeTime;

out vec2 v_TexPos;

uniform mat4 worldTrans;
uniform mat4 cameraTrans;
uniform mat4 projTrans;
uniform bool isDrawFont;

uniform bool isInstanceDraw;
uniform bool isRepeat;
uniform float gTime;


void main()
{
    if(!isInstanceDraw)
    {
        mat4 MVP = projTrans*cameraTrans*worldTrans;
        vec4 outPos = MVP*position;
        gl_Position = outPos;
    }
    else
    {
        float t = 0.0f;
        if(isRepeat)
        {
            t = mod(gTime, lifeTime);
        }
        else
        {
            t = gTime;
        }
        if(t <= lifeTime)
        {
            float xPos = vel.x * t + 0.5f * acc.x * t * t;
            float yPos = vel.y * t + 0.5f * acc.y * t * t;
            mat4 transMat = mat4(1.0f, 0.0f, 0.0f, xPos + addPos.x,
                                 0.0f, 1.0f, 0.0f, yPos + addPos.y,
                                 0.0f, 0.0f, 1.0f, 0.0f,
                                 0.0f, 0.0f, 0.0f, 1.0f);
            transMat = transpose(transMat);
            mat4 MVP = projTrans*cameraTrans*transMat*worldTrans;
            vec4 retVal = MVP*position;
            gl_Position = retVal;
        }
        else
        {
            gl_Position = vec4(-9999.0f, -9999.0f, 0.0f, 1.0f);
        }
    }
    v_TexPos = inputTexPos;
}
