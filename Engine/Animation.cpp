#include "pch.h"

#include "Animation.h"
#include "AnimationFrame.h"

Animation::Animation(std::vector<AnimationFrame*> frames)
{
    m_Frames = frames;
    for (AnimationFrame* frame : frames)
    {
        m_TotalDuration += frame->GetDuration();
    }
}

Animation::~Animation()
{
    for (auto&& frame : m_Frames)
    {
        delete frame;
        frame = nullptr;
    }
}

AnimationFrame* Animation::GetFrame(int frameNr)
{
    return m_Frames[frameNr];
}

std::vector<AnimationFrame*> Animation::GetFrames() const
{
    return m_Frames;
}

float Animation::GetTotalDuration() const
{
    return m_TotalDuration;
}