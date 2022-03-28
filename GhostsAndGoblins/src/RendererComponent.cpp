#include "pch.h"

#include <iostream>
#include <cassert>

#include "RendererComponent.h"
#include "TransformComponent.h"
#include "Texture.h"

RendererComponent::RendererComponent(Entity* parent, Texture* texture)
	: Component(parent),
	m_pTexture{texture}
{
	m_pParentTransform = parent->GetComponent<TransformComponent>();
	assert(m_pParentTransform != nullptr && "Entity has renderer component but not transform component");
}

RendererComponent::~RendererComponent()
{
}

void RendererComponent::Draw() const
{
	TransformComponent* transform = m_pParentTransform;
	Rectf dstRect = Rectf(transform->GetPosition().x, transform->GetPosition().y, 17 * 5, 17 * 5);
	m_pTexture->Draw(dstRect, Rectf(0, 0, 17, 17));
}
