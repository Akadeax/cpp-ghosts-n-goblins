#include <pch.h>
#include "PlayerJumpState.h"

#include <vector>
#include <Animation.h>
#include <AnimationFrame.h>

PlayerJumpState::PlayerJumpState()
	: AnimatorState(new Animation(
		std::vector<AnimationFrame*>
		{
			new AnimationFrame(1.f, Rectf(22 * 3, 25, 22, 25)),
		}
)) {}