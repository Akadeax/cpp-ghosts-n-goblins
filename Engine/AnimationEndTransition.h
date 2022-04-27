#pragma once
#include "AnimatorTransition.h"

class AnimationEndTransition :
    public AnimatorTransition
{
public:
    explicit AnimationEndTransition(std::string origin, std::string destination);
    AnimationEndTransition& operator=(const AnimationEndTransition& rhs) = delete;
    AnimationEndTransition& operator=(AnimationEndTransition&& rhs) = delete;
    AnimationEndTransition(const AnimationEndTransition& rhs) = delete;
    AnimationEndTransition(AnimationEndTransition&& rhs) = delete;
    virtual ~AnimationEndTransition() = default;

    bool ShouldTransition() override;
};
