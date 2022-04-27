#include <pch.h>
#include "PlayerCrouchState.h"

#include <vector>
#include <Animation.h>
#include <AnimationFrame.h>

PlayerCrouchState::PlayerCrouchState()
	: AnimatorState(new Animation(
		std::vector<AnimationFrame*>
{
	new AnimationFrame(1.f, Rectf(22 * 3, 25 * 4, 22, 25)),
}
)) {}