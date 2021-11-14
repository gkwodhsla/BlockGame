#include "ScoreBoard.h"
#include "../Components/TTFComponent.h"

ScoreBoard::ScoreBoard()
{
    scoreText = createComponent<TTFComponent>("font/EvilEmpire.ttf", 56, "what the fuck", this);
    scoreText->attachTo(rootComponent);
    scoreText->setTextColor(1.0f,0.0f,0.0f);
}

ScoreBoard::~ScoreBoard()
{

}

void ScoreBoard::render()
{
    HActor::render();
}

void ScoreBoard::update(const float deltaTime)
{
    HActor::update(deltaTime);
}
