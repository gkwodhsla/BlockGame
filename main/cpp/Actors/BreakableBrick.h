#include "BrickParent.h"

class BreakableBrick: public BrickParent
{
public:
    BreakableBrick(const char* imgPath);
    BreakableBrick() = delete;
    BreakableBrick(const BreakableBrick&) = delete;
    BreakableBrick&operator=(const BreakableBrick&) = delete;
    virtual ~BreakableBrick();
public:
    virtual void render() override;
    virtual void update(const float deltaTime) override;

};
