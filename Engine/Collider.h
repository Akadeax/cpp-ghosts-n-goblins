#pragma once
#include "Component.h"
#include <vector>
#include "Vector2f.h"

class Transform;

class Collider final
	: public Component
{
public:
	explicit Collider(Entity* parent, std::vector<Vector2f> vertices);
	Collider& operator=(const Collider& rhs) = delete;
	Collider& operator=(Collider&& rhs) = delete;
	Collider(const Collider& rhs) = delete;
	Collider(Collider&& rhs) = delete;
	virtual ~Collider();

	void Initialize() override;

	virtual void OnCollisionUpdate(Collider* other, float deltaTime);
	virtual void OnCollisionEnter(Collider* other, float deltaTime);
	virtual void OnCollisionExit(Collider* other, float deltaTime);

	void Update(float deltaTime) override;
	void Draw() const override;

	bool IsTrigger() const;
	void SetTrigger(bool newVal);

	bool CompareTag(std::string tag);

	const std::vector<Vector2f>& GetBaseVertices();
	const std::vector<Vector2f>& GetTransformedVertices();

private:
	Transform* m_pTransform{ nullptr };

	// Whether the collider is pass-through
	bool m_IsTrigger{ false };

	size_t m_VerticesAmount;
	// Non-transformed vertices in relation to the transforms position
	const std::vector<Vector2f> m_BaseVertices;
	// Computed transformed vertices (translated and rotated!)
	std::vector<Vector2f> m_TransformedVertices;
};

