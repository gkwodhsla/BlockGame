#include "BrickParent.h"
enum class BlockColor
{
    BLUE,
    RED,
    GREEN,
    ORANGE,
    PURPLE
};
class PNG;
class ParticleComponent;

class BreakableBrick: public BrickParent
{
public:
    BreakableBrick();
    BreakableBrick(const BreakableBrick&) = delete;
    BreakableBrick&operator=(const BreakableBrick&) = delete;
    virtual ~BreakableBrick();
public:
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    void setBlockToUse(const BlockColor& color);

private:
    ParticleComponent* particle;
    bool isPlay = false;

private:
    static float xPosMin;
    static float xPosMax;
    static float yPosMin;
    static float yPosMax;
    static float xVelMin;
    static float xVelMax;
    static float yVelMin;
    static float yVelMax;
    static float xAccMin;
    static float xAccMax;
    static float yAccMin;
    static float yAccMax;
    static float particleLifeTime;
    static int particleNum;

private:
    static PNG* blueImage;
    static PNG* redImage;
    static PNG* greenImage;
    static PNG* orangeImage;
    static PNG* purpleImage;
};
