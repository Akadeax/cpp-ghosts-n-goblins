#include "PlayerIdleState.h"
#include "Animation.h"
#include "AnimationFrame.h"

PlayerIdleState::PlayerIdleState()
	: AnimatorState
	(
		new Animation(
			std::vector<AnimationFrame*>
			{
				new AnimationFrame(0.5f, Rectf(0, 16, 16, 16)),
				new AnimationFrame(0.5f, Rectf(16, 16, 16, 16)),
			},
			true
		)
	)
{
}
