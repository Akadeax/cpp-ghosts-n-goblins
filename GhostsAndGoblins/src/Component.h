#pragma once

class Entity;
class PhysicsHandler;

class Component
{
public:
	Component& operator=(const Component& other) = delete;
	Component(const Component& other) = delete;
	Component(Component&&) = delete;
	Component& operator=(Component&&) = delete;
	virtual ~Component();

	Entity* GetParent() const;

	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw() const;

protected:
	Entity* m_pParent;

	Component(Entity* parent);

	PhysicsHandler* GetPhysicsHandler() const;
};

