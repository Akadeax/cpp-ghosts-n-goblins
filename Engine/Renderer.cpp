#include "pch.h"

#include <iostream>
#include <cassert>

#include "Renderer.h"
#include "Transform.h"
#include "Texture.h"

Renderer::Renderer(Entity* parent, Texture* texture)
	: Component(parent)
{
	m_pTexture = texture;

}

Renderer::~Renderer()
{
}

void Renderer::Initialize()
{
	m_pParentTransform = m_pParent->GetComponent<Transform>();
	assert(m_pParentTransform != nullptr && "Entity has renderer component but not transform component");
}

void Renderer::Draw() const
{
	glRotatef(m_pParentTransform->GetRotation(), 0.f, 0.f, 1.f);

	glTranslatef(m_pParentTransform->GetPosition().x, m_pParentTransform->GetPosition().y, 0);

	float renderScale = m_pParentTransform->GetScale();
	glScalef(
		m_FlipX ? -renderScale : renderScale,
		m_FlipY ? -renderScale : renderScale,
		0
	);

	DrawSprite();
}

void Renderer::DrawSprite() const
{
	const Transform* transform = m_pParentTransform;
	m_pTexture->DrawCentered(Rectf(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight()));
}

bool Renderer::GetFlipX() const
{
	return m_FlipX;
}

void Renderer::SetFlipX(bool newState)
{
	m_FlipX = newState;
}

bool Renderer::GetFlipY() const
{
	return m_FlipY;
}

void Renderer::SetFlipY(bool newState)
{
	m_FlipY = newState;
}
