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

class BreakableBrick: public BrickParent
{
public:
    BreakableBrick(const char* imgPath);
    BreakableBrick();
    BreakableBrick(const BreakableBrick&) = delete;
    BreakableBrick&operator=(const BreakableBrick&) = delete;
    virtual ~BreakableBrick();
public:
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    void setBlockToUse(const BlockColor& color);

private:
    static PNG* blueImage;
    static PNG* redImage;
    static PNG* greenImage;
    static PNG* orangeImage;
    static PNG* purpleImage;
};
