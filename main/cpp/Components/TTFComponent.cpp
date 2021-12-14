#include "TTFComponent.h"
#include "../Common/Framework.h"
#include "../Common/Renderer.h"

float TTFComponent::rect[] =
        {
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,//아래 사각형
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f//위에 사각형
        };

TTFComponent::TTFComponent(const char *filePath, size_t fontSize, const std::string& content, HActor *owner):content(content)
{
    createFontTexture(filePath, fontSize);
    this->owner = owner;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_DYNAMIC_DRAW);
    auto posLoc = glGetAttribLocation(frameworkInst->curRenderer->getProgramID(), "position");
    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
    auto texLoc = glGetAttribLocation(frameworkInst->curRenderer->getProgramID(), "inputTexPos");
    glEnableVertexAttribArray(texLoc);
    glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(sizeof(float)*3));
}

TTFComponent::~TTFComponent()
{

}

void TTFComponent::render()
{
    HPrimitiveComponent::render();
    auto isFontDrawLoc = glGetUniformLocation(Framework::curRenderer->getProgramID(), "isDrawFont");
    glUniform1i(isFontDrawLoc, true);
    auto tintLoc = glGetUniformLocation(frameworkInst->curRenderer->getProgramID(), "tintColor");
    glUniform3f(tintLoc, tintR,tintG,tintB);
    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;
    glActiveTexture(GL_TEXTURE0);
    std::string::const_iterator c;
    for (c = content.begin(); c != content.end(); c++)
        {
            Character ch = characters[*c];
            float xpos = x + ch.bearing.x * scale;
            float ypos = y - (ch.size.y - ch.bearing.y) * scale;
            float w = ch.size.x * scale;
            float h = ch.size.y * scale;
// update VBO for each character
            float vertices[6][5] = {
                    { xpos, ypos + h, 0.0f ,0.0f, 0.0f },
                    { xpos, ypos, 0.0f,0.0f, 1.0f },
                    { xpos + w, ypos, 0.0f,1.0f, 1.0f },
                    { xpos, ypos + h, 0.0f,0.0f, 0.0f },
                    { xpos + w, ypos, 0.0f,1.0f, 1.0f },
                    { xpos + w, ypos + h, 0.0f,1.0f, 0.0f }
            };
// render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
// update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
// render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
// advance cursors for next glyph (advance is 1/64 pixels)
            x += (ch.advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
        }

}

void TTFComponent::changeFont(const char* filePath, size_t fontSize)
{

}

void TTFComponent::setTextColor(const float r, const float g, const float b)
{
    tintR = r;
    tintG = g;
    tintB = b;
}

void TTFComponent::createFontTexture(const char *filePath, size_t fontSize)
{
    auto error = FT_Init_FreeType(&library);
    if(error)
    {
        PRINT_LOG("error occure", %s);
    }

    size_t fileSize = 0;
    char* buffer = GlobalFunction::readFile(filePath, fileSize);

    error = FT_New_Memory_Face(library,std::vector<unsigned char>(buffer, buffer+fileSize).data(),fileSize,0,&face);
    if (error == FT_Err_Unknown_File_Format)
    {
        PRINT_LOG("font type error(unknown error)", %s);
    }
    else if (error)
    {
        PRINT_LOG("font load error", %s);
    }
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//no byte alingnment
    for(unsigned char c = 0; c < 128; c++)
    {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            PRINT_LOG("failed to load glyph", %s);
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                     face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);
        //내부적으로 8bit 비트맵으로 만들어서 반환해주기 때문에 GL_RED를 쓴다.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };
        characters.insert(std::make_pair(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    delete[] buffer;
    buffer = nullptr;
}
