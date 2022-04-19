#pragma once
#include "Component.h"
#include <vector>
#include "Vector2f.h"

class Transform;

class Collider
	: public Component
{
public:
	explicit Collider(Entity* parent, std::vector<Vector2f> vertices);
	Collider& operator=(const Collider& rhs) = delete;
	Collider& operator=(Collider&& rhs) = delete;
	Collider(const Collider& rhs) = delete;
	Collider(Collider&& rhs) = delete;
	virtual ~Collider() = default;

	void Initialize() override;

	void Update(float deltaTime) override;
	void Draw() const override;

private:
	Transform* m_pTransform{ nullptr };

	size_t m_VerticesAmount;
	std::vector<Vector2f> m_RelativeVertices;
	std::vector<Vector2f> m_TransformedVertices;
};

