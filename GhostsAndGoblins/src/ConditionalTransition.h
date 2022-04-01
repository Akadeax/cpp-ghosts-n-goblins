#pragma once
#include "AnimatorTransition.h"

class AnimatorRenderer;

class ConditionalTransition :
    public AnimatorTransition
{
public:
    ConditionalTransition(
        std::string origin,
        std::string destination,
        std::unordered_map<std::string, int> conditions
    );

    ~ConditionalTransition();

    bool ShouldTransition() override;

private:
    std::unordered_map<std::string, int> m_Conditions;
};
