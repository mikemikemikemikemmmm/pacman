#include "pacman.h"
const AnimationDataMap PacmanObj::m_animationDataMap = {
        {"die", AnimationData{0,240,12,false} },
        {"up", AnimationData{0,40,3,true} },
        {"down", AnimationData{0,60,3,true} },
        {"right", AnimationData{0,20,3,true} },
        {"left", AnimationData{0,0,3,true} },
        {"stay", AnimationData{40,0,1,true} },
};
