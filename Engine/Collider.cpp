#include "pch.h"

#include <cassert>

#include "PhysicsHandler.h"
#include "Collider.h"
#include "utils.h"
#include "Entity.h"
#include "Transform.h"
#include "Scene.h"
#include "Camera.h"

Collider::Collider(Entity* parent, std::vector<Vector2f> vertices)
	: Component(parent), m_BaseVertices{vertices}
{
	assert(vertices.size() > 2 && "Not enough vertices given for collider");
	m_VerticesAmount = vertices.size();
	m_TransformedVertices = std::vector<Vector2f>(m_VerticesAmount);
}

Collider::~Collider()
{
	GetPhysicsHandler()->RemoveCollider(this);
}

void Collider::Initialize()
{
	m_pTransform = m_pParent->GetComponent<Transform>();
	assert(m_pTransform != nullptr && "Entity has collider but no transform");
	GetPhysicsHandler()->AddCollider(this);
}

void Collider::OnCollisionUpdate(Collider* other, float deltaTime) { }
void Collider::OnCollisionEnter(Collider* other, float deltaTime) { }
void Collider::OnCollisionExit(Collider* other, float deltaTime) { }

void Collider::Update(float deltaTime)
{
	float rotation = m_pTransform->GetRotation() * (utils::g_Pi / 180);

	float rotSin = std::sin(rotation);
	float rotCos = std::cos(rotation);

	for (size_t i{ 0 }; i < m_VerticesAmount; i++)
	{
		Vector2f base = m_BaseVertices[i];

		// Scale
		Vector2f scaled = base * m_pTransform->GetScale();
		// Rotate
		float newX = rotCos * scaled.x - rotSin * scaled.y;
		float newY = rotSin * scaled.x + rotCos * scaled.y;
		// Translate
		newX += m_pTransform->GetPosition().x;
		newY += m_pTransform->GetPosition().y;

		m_TransformedVertices[i] = Vector2f(newX, newY);
	}
}

void Collider::Draw() const
{
	utils::SetColor(Color4f(1, 0, 0, 1));
	size_t verticesAmt = m_TransformedVertices.size();
	for (int i{ 0 }; i < verticesAmt; i++)
	{
		utils::DrawPolygon(m_TransformedVertices, true, 2.f);
	}
}

bool Collider::IsTrigger() const
{
	return m_IsTrigger;
}

void Collider::SetTrigger(bool newVal)
{
	m_IsTrigger = newVal;
}

bool Collider::CompareTag(std::string tag)
{
	return m_pParent->GetTag() == tag;
}

const std::vector<Vector2f>& Collider::GetBaseVertices()
{
	return m_BaseVertices;
}

const std::vector<Vector2f>& Collider::GetTransformedVertices()
{
	return m_TransformedVertices;
}
