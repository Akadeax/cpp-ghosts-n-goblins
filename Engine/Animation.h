#pragma once
#include <vector>

class AnimationFrame;

class Animation final
{
public:
	explicit Animation(std::vector<AnimationFrame*> frames);
	Animation& operator=(const Animation& rhs) = delete;
	Animation& operator=(Animation&& rhs) = delete;
	Animation(const Animation& rhs) = delete;
	Animation(Animation&& rhs) = delete;
	virtual ~Animation();

	AnimationFrame* GetFrame(int frameNr);
	std::vector<AnimationFrame*> GetFrames() const;
	float GetTotalDuration() const;

private:
	std::vector<AnimationFrame*> m_Frames;
	float m_TotalDuration = 0;
};