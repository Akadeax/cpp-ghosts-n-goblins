#include "pch.h"
#include "AnimatorState.h"
#include "Animation.h"

AnimatorState::AnimatorState(Animation* anim)
{
	m_pAnimation = anim;
}

AnimatorState::~AnimatorState()
{
	delete m_pAnimation;
}

Animation* AnimatorState::GetAnimation() const
{
	return m_pAnimation;
}

void AnimatorState::OnStateEnter(AnimatorRenderer* animator)
{
}

void AnimatorState::OnStateUpdate(AnimatorRenderer* animator, float deltaTime)
{
}

void AnimatorState::OnStateExit(AnimatorRenderer* animator)
{
}
