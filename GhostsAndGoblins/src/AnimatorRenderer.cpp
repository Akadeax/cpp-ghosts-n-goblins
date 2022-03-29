#include "pch.h"

#include "AnimatorRenderer.h"
#include "AnimatorState.h"
#include "AnimationFrame.h"
#include "Animation.h"
#include "Texture.h"
#include "Transform.h"
#include "AnimatorTransition.h"

AnimatorRenderer::AnimatorRenderer(
	Entity* parent,
	Texture* texture,
	std::unordered_map<std::string, AnimatorState*> states,
	std::set<AnimatorTransition*> transitions,
	std::string entryState
) : Renderer(parent, texture)
{
	m_States = states;
	m_Transitions = transitions;
	m_CurrentState = m_States[entryState];
}

AnimatorRenderer::~AnimatorRenderer()
{
	for (auto& pair : m_States)
	{
		delete pair.second;
	}

	for (auto& transition : m_Transitions)
	{
		delete transition;
	}
}

int AnimatorRenderer::GetParameter(std::string paramName)
{
	return m_Parameters[paramName];
}

void AnimatorRenderer::SetParameter(std::string paramName, int newValue)
{
	m_Parameters[paramName] = newValue;
}

void AnimatorRenderer::Pause()
{
	m_IsPaused = true;
}

void AnimatorRenderer::Unpause()
{
	m_IsPaused = false;
}

bool AnimatorRenderer::IsPaused() const
{
	return m_IsPaused;
}

void AnimatorRenderer::Update(float deltaTime)
{
	if (IsPaused()) return;

	m_CurrentAnimationTime += deltaTime;

	bool animationFinished = m_CurrentAnimationTime >= m_CurrentState->GetAnimation()->GetTotalDuration();
	bool canLoop = m_CurrentState->GetAnimation()->CanLoop();
	if (animationFinished && canLoop)
	{
		m_CurrentAnimationTime = 0;
	}

	// Determine current animation frame
	float currentIntervalEnd = 0;
	std::vector<AnimationFrame*> frames = m_CurrentState->GetAnimation()->GetFrames();
	for (int i = 0; i < frames.size(); i++)
	{
		currentIntervalEnd += frames[i]->GetDuration();
		if (m_CurrentAnimationTime < currentIntervalEnd)
		{
			m_CurrentAnimationFrame = i;
			break;
		}
	}
}

void AnimatorRenderer::Draw() const
{
	std::cout << m_CurrentAnimationFrame << std::endl;

	AnimationFrame* currentFrame = m_CurrentState->GetAnimation()->GetFrame(m_CurrentAnimationFrame);
	m_pTexture->Draw(
		Rectf(
			m_pParentTransform->GetPosition().x,
			m_pParentTransform->GetPosition().y,
			currentFrame->GetSpriteData().width,
			currentFrame->GetSpriteData().height
		),
		currentFrame->GetSpriteData()
	);
}
