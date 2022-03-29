#pragma once
#include <string>

class AnimatorRenderer;
class Animation;

class AnimatorState
{
public:
	AnimatorState(Animation* anim);
	virtual ~AnimatorState();

	Animation* GetAnimation() const;

	virtual void OnStateEnter(AnimatorRenderer* animator);
	virtual void OnStateUpdate(AnimatorRenderer* animator, float deltaTime);
	virtual void OnStateExit(AnimatorRenderer* animator);

private:
	Animation* m_pAnimation;
};

