#include "Renderer.h"
#include "Program.h"

Renderer::Renderer(const char *VSPath, const char *FSPath)
{
    curProgram = new Program(VSPath, FSPath);
    programID = curProgram->programID;
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glUseProgram(programID);
}

Renderer::~Renderer()
{
    if(curProgram)
    {
        delete curProgram;
        curProgram = nullptr;
    }
}

void Renderer::setClearColor(const float r, const float g, const float b, const float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::enableGLFeature(const GLbitfield bit)
{
    glEnable(bit);
}

void Renderer::unableGLFeature(const GLbitfield bit)
{
    glDisable(bit);
}

void Renderer::addClearBit(const GLbitfield bit)
{
    clearBits.emplace_back((GLuint)bit);
}

void Renderer::eraseClearBit(const GLbitfield bit)
{
    for(int i=0;i<clearBits.size();++i)
    {
        if(clearBits[i] == (GLuint)bit)
        {
            clearBits.erase(clearBits.begin() + i);
        }
    }
}

void Renderer::changeProgram(const char *VSPath, const char *FSPath)
{
    if(curProgram)
    {
        delete curProgram;
        curProgram = nullptr;
    }
    curProgram = new Program(VSPath, FSPath);
    programID = curProgram->programID;
}

void Renderer::clearRenderer()
{
    for(auto&val : clearBits)
    {
        glClear(val);
    }
}