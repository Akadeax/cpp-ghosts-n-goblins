#pragma once
#include "Renderer.h"
#include <unordered_map>

class AnimatorState;
class AnimatorTransition;

class AnimatorRenderer :
    public Renderer
{
public:
    AnimatorRenderer(
        Entity* parent,
        Texture* texture,
        std::unordered_map<std::string, AnimatorState*> states,
        std::list<AnimatorTransition*> transitions,
        std::string entryState
    );
    AnimatorRenderer(const AnimatorRenderer& other) = delete;
    AnimatorRenderer& operator=(const AnimatorRenderer& other) = delete;
    AnimatorRenderer(AnimatorRenderer&& other) = delete;
    AnimatorRenderer& operator=(AnimatorRenderer&& other) = delete;
    ~AnimatorRenderer();

    int GetParameter(std::string paramName);
    void SetParameter(std::string paramName, int newValue);

    AnimatorState* GetCurrentState() const;
    std::unordered_map<std::string, AnimatorState*> GetStates() const;

    void SetState(std::string newState);

    void Pause();
    void Unpause();
    bool IsPaused() const;

    void Update(float deltaTime) override;
    void DrawSprite() const override;

    float GetCurrentStateTime() const;
    float GetCurrentLoopTime() const;
    int GetCurrentLoopFrame() const;

private:
    std::unordered_map<std::string, AnimatorState*> m_States;
    std::list<AnimatorTransition*> m_Transitions;
    std::unordered_map<std::string, int> m_Parameters;

    AnimatorState* m_CurrentState;

    bool m_IsPaused = false;
    // The time the animator has been in the current state
    float m_CurrentStateTime = 0.f;
    // Time until animation has to be looped
    float m_CurrentLoopTime = 0.f;
    int m_CurrentLoopFrame = 0;
};

