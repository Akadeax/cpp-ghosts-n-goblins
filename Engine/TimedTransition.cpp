#include "pch.h"
#include "TimedTransition.h"

#include "AnimatorRenderer.h"

TimedTransition::TimedTransition(std::string origin, std::string destination, float duration)
	: AnimatorTransition(origin, destination), m_Duration{ duration }
{
}

bool TimedTransition::ShouldTransition()
{
	return m_pAnimator->GetCurrentStateTime() >= m_Duration;
}
