#include "pch.h"

#include "AnimationEndTransition.h"
#include "AnimatorState.h"
#include "Animation.h"

bool AnimationEndTransition::ShouldTransition()
{
	const AnimatorState* transitionOriginState = m_pAnimator->GetStates()[m_OriginState];
	const float& originAnimDuration = transitionOriginState->GetAnimation()->GetTotalDuration();
	return m_pAnimator->GetCurrentStateTime() >= originAnimDuration;
}
