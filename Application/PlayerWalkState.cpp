#include <pch.h>
#include "PlayerWalkState.h"

#include <vector>
#include <Animation.h>
#include <AnimationFrame.h>

PlayerWalkState::PlayerWalkState()
	: AnimatorState(new Animation(
		std::vector<AnimationFrame*>
		{
			new AnimationFrame(0.15f, Rectf(0, 50, 22, 25)),
			new AnimationFrame(0.15f, Rectf(22, 50, 22, 25)),
			new AnimationFrame(0.15f, Rectf(44, 50, 22, 25)),
			new AnimationFrame(0.15f, Rectf(22, 50, 22, 25)),
		}
)) {}