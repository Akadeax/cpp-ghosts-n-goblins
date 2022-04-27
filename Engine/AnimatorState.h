#pragma once
#include <string>

class AnimatorRenderer;
class Animation;

class AnimatorState
{
public:
	explicit AnimatorState(Animation* anim);
	AnimatorState& operator=(const AnimatorState& rhs) = delete;
	AnimatorState& operator=(AnimatorState&& rhs) = delete;
	AnimatorState(const AnimatorState& rhs) = delete;
	AnimatorState(AnimatorState&& rhs) = delete;
	virtual ~AnimatorState();

	Animation* GetAnimation() const;

	virtual void OnStateEnter(AnimatorRenderer* animator);
	virtual void OnStateUpdate(AnimatorRenderer* animator, float deltaTime);
	virtual void OnStateExit(AnimatorRenderer* animator);

private:
	Animation* m_pAnimation;
};

