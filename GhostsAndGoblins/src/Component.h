#pragma once

class Entity;

class Component
{
public:
	Component& operator=(const Component& other) = delete;
	Component(const Component& other) = delete;
	Component(Component&&) = delete;
	Component& operator=(Component&&) = delete;
	virtual ~Component();

	Entity* GetParent() const;

	virtual void Update(float deltaTime);
	virtual void Draw() const;

protected:
	Component(Entity* parent);

private:
	Entity* m_pParent;
};

