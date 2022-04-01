#include "pch.h"

#include "AnimatorTransition.h"

AnimatorTransition::AnimatorTransition(std::string origin, std::string destination)
{
	m_OriginState = origin;
	m_DestinationState = destination;
}

AnimatorTransition::~AnimatorTransition()
{
}

std::string AnimatorTransition::GetOriginState() const
{
	return m_OriginState;
}

std::string AnimatorTransition::GetDestinationState() const
{
	return m_DestinationState;
}

void AnimatorTransition::SetAnimatorRef(AnimatorRenderer* animator)
{
	m_pAnimator = animator;
}
