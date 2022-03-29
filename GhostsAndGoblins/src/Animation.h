#pragma once
#include <vector>

class AnimationFrame;

class Animation final
{
public:
	Animation(std::vector<AnimationFrame*> frames, bool canLoop);
	~Animation();

	AnimationFrame* GetFrame(int frameNr);
	std::vector<AnimationFrame*> GetFrames() const;
	float GetTotalDuration() const;
	bool CanLoop() const;

private:
	std::vector<AnimationFrame*> m_Frames;
	bool m_CanLoop;
	float m_TotalDuration;
};

