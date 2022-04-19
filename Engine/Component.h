#pragma once

class Entity;
class PhysicsHandler;

class Component
{
public:
	explicit Component(Entity* parent);
	Component& operator=(const Component& rhs) = delete;
	Component& operator=(Component&& rhs) = delete;
	Component(const Component& rhs) = delete;
	Component(Component&& rhs) = delete;
	virtual ~Component() = default;

	Entity* GetParent() const;

	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw() const;

protected:
	Entity* m_pParent;

};
