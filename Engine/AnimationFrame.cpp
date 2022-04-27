#include "pch.h"

#include "AnimationFrame.h"

AnimationFrame::AnimationFrame(float duration, Rectf spriteData)
    : m_Duration{ duration }, m_SpriteData{ spriteData }
{
}

float AnimationFrame::GetDuration() const
{
    return m_Duration;
}

Rectf AnimationFrame::GetSpriteData() const
{
    return m_SpriteData;
}
