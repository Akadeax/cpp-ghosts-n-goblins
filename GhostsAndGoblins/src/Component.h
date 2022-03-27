#pragma once

class Entity;

class Component
{
public:
	enum class Type
	{
		Transform, Renderer
	};
	Component& operator=(const Component& other) = delete;
	Component(const Component& other) = delete;
	Component(Component&&) = delete;
	Component& operator=(Component&&) = delete;
	virtual ~Component();

	Entity* GetParent() const;

	Component::Type GetType() const;

	virtual void Update(float deltaTime);
	virtual void Draw() const;

protected:
	Component(Component::Type type, Entity* parent);

private:
	Entity* m_pParent;
	Component::Type m_Type;
};

