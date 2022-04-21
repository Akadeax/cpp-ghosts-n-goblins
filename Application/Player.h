#pragma once
#include <Component.h>

class Transform;
class PhysicsBody;
class AnimatorRenderer;

class Player final :
    public Component
{
public:
    explicit Player(Entity* parent);
    Player& operator=(const Player& rhs) = delete;
    Player& operator=(Player&& rhs) = delete;
    Player(const Player& rhs) = delete;
    Player(Player&& rhs) = delete;
    virtual ~Player() = default;

    void Initialize() override;

    void Update(float deltaTime) override;
    void Draw() const override;

private:
    Transform* m_pTransform{ nullptr };
    PhysicsBody* m_pPhysicsBody{ nullptr };
    AnimatorRenderer* m_pAnimator{ nullptr };

    const float m_GroundedCheckYOffset{ -13.f };
    const float m_GroundedCheckXSize{ 20.f };

    float m_GravityFactor{ 9.f };
    float m_MoveSpeed{ 80.f };

    int m_CurrentMoveDir{ 0 };
    float m_JumpStrength{ 200.f };

    bool m_IsGrounded{ false };

    void UpdateMovement();
    void CheckGrounded();
    void UpdateJump();
};

