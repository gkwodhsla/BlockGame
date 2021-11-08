#version 300 es

in vec4 position;

void main()
{
    vec4 outPos = position;

    gl_Position = outPos;
}