#pragma once
#include <vector>

class AnimationFrame;

class Animation final
{
public:
	Animation(std::vector<AnimationFrame*> frames);
	~Animation();

	AnimationFrame* GetFrame(int frameNr);
	std::vector<AnimationFrame*> GetFrames() const;
	float GetTotalDuration() const;

private:
	std::vector<AnimationFrame*> m_Frames;
	float m_TotalDuration = 0;
};