#pragma once
#include "HPrimitiveComponent.h"
#include <ft2build.h>
#include <map>
#include <string>
#include FT_FREETYPE_H

struct Character
{
    unsigned int textureID;
    glm::ivec2 size; // 해당 글리프의 width, height
    glm::ivec2 bearing; //해당 글리프가 원점에서 얼마나 떨어져있는가
    signed long advance; //다음 글리프로부터의 거리
};

class TTFComponent: public HPrimitiveComponent
{
public:
    TTFComponent() = delete;
    TTFComponent(const TTFComponent&) = delete;
    TTFComponent& operator=(const TTFComponent&) = delete;
    TTFComponent(const char* filePath, size_t fontSize,const std::string& content ,HActor* owner);
    virtual ~TTFComponent();

public:
    void render() override;

public:
    void changeFont(const char* filePath, size_t fontSize);
    void setTextColor(const float r, const float g, const float b);

private:
    void createFontTexture(const char* filePath, size_t fontSize);

private:
    GLuint VBO;
    GLuint width;
    GLuint height;
    static float rect[];
    bool isTintEnabled = false;
    float tintR = 1.0f;
    float tintG = 1.0f;
    float tintB = 1.0f;
    FT_Library library;
    FT_Face face;
    std::map<char, Character> characters;
    std::string content;
};
