#pragma once
#include <GLES3/gl3.h>

class Program
{
public:
    Program() = delete;
    Program(const Program&) = delete;
    virtual ~Program();
    Program& operator=(const Program&) = delete;
    Program(const char* VSPath, const char* FSPath);

    GLuint programID = -1;
private:
    GLuint compileShader(GLenum shaderType, const char* sourceLoc);
    GLuint createProgram(GLuint VSID, GLuint FSID);
};