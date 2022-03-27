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

	std::string GetType() const;

	virtual void Update(float deltaTime);
	virtual void Draw() const;

protected:
	Component(std::string type, Entity* parent);

private:
	Entity* m_pParent;
	std::string m_Type;
};

