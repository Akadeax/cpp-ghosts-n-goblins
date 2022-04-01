#pragma once
#include "AnimatorRenderer.h"

class AnimatorTransition
{
public:
	AnimatorTransition(std::string origin, std::string destination);
	virtual ~AnimatorTransition();

	std::string GetOriginState() const;
	std::string GetDestinationState() const;

	virtual bool ShouldTransition() = 0;

	void SetAnimatorRef(AnimatorRenderer* animator);

protected:
	AnimatorRenderer* m_pAnimator;

	std::string m_OriginState;
	std::string m_DestinationState;
};