#pragma once
#if defined(__ANDROID__) || defined(ANDROID)
#include <GLES3/gl3.h>
#elif defined(IOS)
#include <OpenGLES/ES3/gl.h>
#endif
class Program
{
public:
    Program() = delete;
    Program(const Program&) = delete;
    virtual ~Program();
    Program& operator=(const Program&) = delete;
    Program(const char* VSPath, const char* FSPath);

public:
    GLuint programID = -1;

private:
    GLuint compileShader(GLenum shaderType, const char* sourceLoc);
    GLuint createProgram(GLuint VSID, GLuint FSID);
};