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
	m_pParentTransform = parent->GetComponent<Transform>();
	assert(m_pParentTransform != nullptr && "Entity has renderer component but not transform component");
}

Renderer::~Renderer()
{
}

void Renderer::Draw() const
{
	const float& rendScale = m_pParentTransform->GetScale();

	glTranslatef(m_pParentTransform->GetPosition().x, m_pParentTransform->GetPosition().y, 0);
	glScalef(
		m_FlipX ? -rendScale : rendScale,
		m_FlipY ? -rendScale : rendScale,
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


