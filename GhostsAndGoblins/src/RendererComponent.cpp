#include "pch.h"

#include "RendererComponent.h"
#include <iostream>
#include "Texture.h"
#include "TransformComponent.h"
#include <cassert>

RendererComponent::RendererComponent(Entity* parent, Texture* texture)
	: Component(Component::Type::Renderer, parent),
	m_pTexture{texture}
{
	m_pParentTransform = parent->GetComponent<TransformComponent>(Component::Type::Transform);
	assert(m_pParentTransform != nullptr);
}

RendererComponent::~RendererComponent()
{
	delete m_pTexture;
}

void RendererComponent::Draw() const
{
	TransformComponent* transform = m_pParentTransform;
	Rectf dstRect = Rectf(transform->GetPosition().x, transform->GetPosition().y, 17 * 5, 17 * 5);
	m_pTexture->Draw(dstRect, Rectf(0, 0, 17, 17));
}
