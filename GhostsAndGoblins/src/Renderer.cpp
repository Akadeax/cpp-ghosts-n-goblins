#include "pch.h"

#include <iostream>
#include <cassert>

#include "Renderer.h"
#include "Transform.h"
#include "Texture.h"

Renderer::Renderer(Entity* parent, Texture* texture)
	: Component(parent),
	m_pTexture{texture}
{
	m_pParentTransform = parent->GetComponent<Transform>();
	assert(m_pParentTransform != nullptr && "Entity has renderer component but not transform component");
}

Renderer::~Renderer()
{
}

void Renderer::Draw() const
{
	Transform* transform = m_pParentTransform;
	Rectf dstRect = Rectf(
		transform->GetPosition().x,
		transform->GetPosition().y,
		m_pTexture->GetWidth(),
		m_pTexture->GetHeight());

	m_pTexture->Draw(dstRect, Rectf(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight()));
}
