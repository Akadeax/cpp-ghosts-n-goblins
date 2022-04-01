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
	std::list<AnimatorTransition*> transitions,
	std::string entryState
) : Renderer(parent, texture)
{
	m_States = states;
	m_Transitions = transitions;
	m_CurrentState = m_States[entryState];

	for (auto& transition : m_Transitions)
	{
		transition->SetAnimatorRef(this);
	}
}

AnimatorRenderer::~AnimatorRenderer()
{
	for (auto& state : m_States)
	{
		delete state.second;
		state.second = nullptr;
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

AnimatorState* AnimatorRenderer::GetCurrentState() const
{
	return m_CurrentState;
}

std::unordered_map<std::string, AnimatorState*> AnimatorRenderer::GetStates() const
{
	return m_States;
}

void AnimatorRenderer::SetState(std::string newState)
{
	if (m_States[newState] == m_CurrentState) return;

	m_CurrentLoopFrame = 0;
	m_CurrentLoopTime = 0;
	m_CurrentStateTime = 0;

	m_CurrentState->OnStateExit(this);
	m_CurrentState = m_States[newState];
	m_CurrentState->OnStateEnter(this);
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

	m_CurrentState->OnStateUpdate(this, deltaTime);

	m_CurrentStateTime += deltaTime;
	m_CurrentLoopTime += deltaTime;


	if (m_CurrentLoopTime >= m_CurrentState->GetAnimation()->GetTotalDuration())
	{
		m_CurrentLoopTime = 0;
	}

	// Determine current animation frame
	float currentIntervalEnd = 0;
	std::vector<AnimationFrame*> frames = m_CurrentState->GetAnimation()->GetFrames();
	for (int i = 0; i < frames.size(); i++)
	{
		currentIntervalEnd += frames[i]->GetDuration();
		if (m_CurrentLoopTime < currentIntervalEnd)
		{
			m_CurrentLoopFrame = i;
			break;
		}
	}

	// Check whether animator should transition states
	for (AnimatorTransition* transition : m_Transitions)
	{
		bool inCorrectOriginState = m_CurrentState == m_States[transition->GetOriginState()];
		bool shouldTransition = transition->ShouldTransition();
		if (inCorrectOriginState && shouldTransition)
		{
			SetState(transition->GetDestinationState());
			break;
		}
	}
}

void AnimatorRenderer::DrawSprite() const
{
	AnimationFrame* currentFrame = m_CurrentState->GetAnimation()->GetFrame(m_CurrentLoopFrame);
	m_pTexture->DrawCentered(
		currentFrame->GetSpriteData()
	);
}

float AnimatorRenderer::GetCurrentStateTime() const
{
	return m_CurrentStateTime;
}

float AnimatorRenderer::GetCurrentLoopTime() const
{
	return m_CurrentLoopTime;
}

int AnimatorRenderer::GetCurrentLoopFrame() const
{
	return m_CurrentLoopFrame;
}
