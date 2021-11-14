#pragma once
#include "HActor.h"

class TTFComponent;

class ScoreBoard: public HActor
{
public:
    ScoreBoard();
    ScoreBoard(const ScoreBoard&) = delete;
    ScoreBoard&operator=(const ScoreBoard&) = delete;
    virtual ~ScoreBoard();

public:
    virtual void render() override;
    virtual void update(const float deltaTime) override;

private:
    TTFComponent* scoreText = nullptr;
};