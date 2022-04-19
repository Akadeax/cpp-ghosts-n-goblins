#include "pch.h"

#include "Collider.h"
#include "utils.h"
#include "Entity.h"
#include "Transform.h"
#include "Scene.h"
#include "Camera.h"
#include <cassert>

Collider::Collider(Entity* parent, std::vector<Vector2f> vertices)
	: Component(parent)
{
	assert(vertices.size() > 2 && "Not enough vertices given for collider");
	m_VerticesAmount = vertices.size();

	m_RelativeVertices = vertices;
	m_TransformedVertices = std::vector<Vector2f>(m_VerticesAmount);
}

void Collider::Initialize()
{
	m_pTransform = m_pParent->GetComponent<Transform>();
	assert(m_pTransform != nullptr && "Entity has collider but no transform");
}

void Collider::Update(float deltaTime)
{
	float rotation = m_pTransform->GetRotation() * (utils::g_Pi / 180);

	float rotSin = std::sin(rotation);
	float rotCos = std::cos(rotation);

	for (size_t i{ 0 }; i < m_VerticesAmount; i++)
	{
		Vector2f v = m_RelativeVertices[i];
		float newX = (rotCos * v.x - rotSin * v.y) + m_pTransform->GetPosition().x;
		float newY = (rotSin * v.x + rotCos * v.y) + m_pTransform->GetPosition().y;
		m_TransformedVertices[i] = Vector2f(newX, newY);
	}
}

void Collider::Draw() const
{
	utils::SetColor(Color4f(1, 0, 0, 1));
	size_t verticesAmt = m_TransformedVertices.size();
	for (int i{ 0 }; i < verticesAmt; i++)
	{
		utils::DrawPolygon(m_TransformedVertices, true, 3.f);
	}
}
