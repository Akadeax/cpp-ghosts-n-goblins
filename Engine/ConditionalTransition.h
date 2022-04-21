#pragma once
#include <unordered_map>

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
    ConditionalTransition& operator=(const ConditionalTransition& rhs) = delete;
    ConditionalTransition& operator=(ConditionalTransition&& rhs) = delete;
    ConditionalTransition(const ConditionalTransition& rhs) = delete;
    ConditionalTransition(ConditionalTransition&& rhs) = delete;
    virtual ~ConditionalTransition() = default;

    bool ShouldTransition() override;

private:
    std::unordered_map<std::string, int> m_Conditions;
};
