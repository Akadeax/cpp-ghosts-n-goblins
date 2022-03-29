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
        std::set<AnimatorTransition*> transitions,
        std::string entryState
    );
    AnimatorRenderer(const AnimatorRenderer& other) = delete;
    AnimatorRenderer& operator=(const AnimatorRenderer& other) = delete;
    AnimatorRenderer(AnimatorRenderer&& other) = delete;
    AnimatorRenderer& operator=(AnimatorRenderer&& other) = delete;
    ~AnimatorRenderer();

    int GetParameter(std::string paramName);
    void SetParameter(std::string paramName, int newValue);

    void Pause();
    void Unpause();
    bool IsPaused() const;

    void Update(float deltaTime) override;
    void Draw() const override;

private:
    std::unordered_map<std::string, AnimatorState*> m_States;
    std::set<AnimatorTransition*> m_Transitions;
    std::unordered_map<std::string, int> m_Parameters;

    AnimatorState* m_CurrentState;

    bool m_IsPaused = false;
    float m_CurrentAnimationTime = 0.f;
    int m_CurrentAnimationFrame = 0;
};

