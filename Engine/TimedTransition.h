#pragma once
#include "AnimatorTransition.h"

class TimedTransition :
    public AnimatorTransition
{
public:
    TimedTransition(std::string origin, std::string destination, float duration);
    TimedTransition& operator=(const TimedTransition& rhs) = delete;
    TimedTransition& operator=(TimedTransition&& rhs) = delete;
    TimedTransition(const TimedTransition& rhs) = delete;
    TimedTransition(TimedTransition&& rhs) = delete;
    virtual ~TimedTransition() = default;

    bool ShouldTransition() override;

private:
    float m_Duration;
};
