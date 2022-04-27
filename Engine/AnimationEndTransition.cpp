#include "pch.h"
#include "AnimationEndTransition.h"

#include "AnimatorState.h"
#include "Animation.h"
#include "AnimatorRenderer.h"

AnimationEndTransition::AnimationEndTransition(std::string origin, std::string destination)
	: AnimatorTransition(origin, destination)
{
}

bool AnimationEndTransition::ShouldTransition()
{
	// check if we've been in the state for at least the time of the animation
	const AnimatorState* transitionOriginState = m_pAnimator->GetStates()[m_OriginState];
	const float& originAnimDuration = transitionOriginState->GetAnimation()->GetTotalDuration();
	return m_pAnimator->GetCurrentStateTime() >= originAnimDuration;
}
