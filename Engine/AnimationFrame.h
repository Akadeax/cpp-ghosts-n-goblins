#pragma once
#include "structs.h"
#include "Vector2f.h"

class AnimationFrame final
{
public:
	explicit AnimationFrame(float duration, Rectf spriteData);
	AnimationFrame& operator=(const AnimationFrame& rhs) = delete;
	AnimationFrame& operator=(AnimationFrame&& rhs) = delete;
	AnimationFrame(const AnimationFrame& rhs) = delete;
	AnimationFrame(AnimationFrame&& rhs) = delete;
	virtual ~AnimationFrame() = default;

	float GetDuration() const;
	Rectf GetSpriteData() const;

private:
	float m_Duration;
	Rectf m_SpriteData;
};