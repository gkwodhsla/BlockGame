#include "Common.h"
#include "Framework.h"
#include "../Levels/HLevelBase.h"

HLevelBase * GlobalFunction::getLevel()
{
    return Framework::curLevel;
}
