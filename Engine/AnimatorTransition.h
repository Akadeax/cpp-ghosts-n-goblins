#pragma once

class AnimatorRenderer;

class AnimatorTransition
{
public:
	explicit AnimatorTransition(std::string origin, std::string destination);
	AnimatorTransition& operator=(const AnimatorTransition& rhs) = delete;
	AnimatorTransition& operator=(AnimatorTransition&& rhs) = delete;
	AnimatorTransition(const AnimatorTransition& rhs) = delete;
	AnimatorTransition(AnimatorTransition&& rhs) = delete;
	virtual ~AnimatorTransition();

	std::string GetOriginState() const;
	std::string GetDestinationState() const;

	// If true, the transition is triggered
	virtual bool ShouldTransition() = 0;

	void SetAnimatorRef(AnimatorRenderer* animator);

protected:
	AnimatorRenderer* m_pAnimator;

	std::string m_OriginState;
	std::string m_DestinationState;
};