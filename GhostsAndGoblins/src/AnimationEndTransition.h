#pragma once
#include "AnimatorTransition.h"

class AnimationEndTransition :
    public AnimatorTransition
{
    AnimationEndTransition(std::string origin, std::string destination);

    bool ShouldTransition() override;
};



