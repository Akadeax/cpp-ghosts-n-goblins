#pragma once
#include "structs.h"
#include "Vector2f.h"

class AnimationFrame final
{
public:
	AnimationFrame(float duration, Rectf spriteData);

	float GetDuration() const;
	Rectf GetSpriteData() const;

private:
	float m_Duration;
	Rectf m_SpriteData;
};