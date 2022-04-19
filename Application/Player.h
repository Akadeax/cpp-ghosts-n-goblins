#pragma once
#include <Component.h>

class Transform;

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

    void Update(float deltaTime) override;
    void Initialize() override;

private:
    Transform* m_pTransform{ nullptr };
    const float m_MoveSpeed{ 90.f };
};

