#include "Program.h"
#include "Framework.h"
#include "Common.h"

#include <fstream>
#include <iterator>
#include <string>

Program::Program(const char *VSPath, const char *FSPath)
{
    GLuint VSID = compileShader(GL_VERTEX_SHADER, VSPath);
    GLuint FSID = compileShader(GL_FRAGMENT_SHADER, FSPath);
    programID = createProgram(VSID, FSID);
}

Program::~Program()
{
    if(programID!=-1)
    {
        glDeleteProgram(programID);
        programID = -1;
    }
}

GLuint Program::compileShader(GLenum shaderType, const char *sourceLoc)
{
    size_t fileSize = 0;
    char* buffer = GlobalFunction::readFile(sourceLoc, fileSize);

    GLuint shader = glCreateShader(shaderType);
    //셰이더 오브젝트 생성
    glShaderSource(shader, 1, &buffer, nullptr);
    //셰이더 소스코드 부착
    glCompileShader(shader);
    //컴파일
    delete[] buffer;
    buffer = nullptr;
    //소스코드를 컴파일하면 할당해줘야한다.

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen)
        {
            char *buf = new char[infoLen];
            if(buf)
            {
                glGetShaderInfoLog(shader, infoLen, nullptr, buf);
                PRINT_LOG(buf, %s);
                delete[] buf;
                buf = nullptr;
            }
        }
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

GLuint Program::createProgram(GLuint VSID, GLuint FSID)
{
    if(!VSID||!FSID)
    {
        return 0;
    }

    GLuint program = glCreateProgram();
    if(program)
    {
        glAttachShader(program, VSID);
        glAttachShader(program, FSID);
        glLinkProgram(program);
    }
    GLint linkStatus = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if(!linkStatus)
    {
        GLint bufLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
        if(bufLen)
        {
            char *buf = new char[bufLen];
            if(buf)
            {
                PRINT_LOG(buf, %s);
                delete[] buf;
                buf = nullptr;
            }
        }
        glDeleteProgram(program);
        program = 0;
    }

    glDeleteShader(VSID);
    glDeleteShader(FSID);

    return program;
}
