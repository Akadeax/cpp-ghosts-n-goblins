#include "pch.h"

#include "PlayerIdleState.h"
#include <vector>
#include "Animation.h"
#include "AnimationFrame.h"

PlayerIdleState::PlayerIdleState()
	: AnimatorState(new Animation
	(
		std::vector<AnimationFrame*>
{
	new AnimationFrame(1.f, Rectf(22, 25, 22, 25)),
}
)) {}