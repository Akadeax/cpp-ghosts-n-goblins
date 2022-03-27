#pragma once
#include "Entity.h"

class Texture;
class TransformComponent;

class RendererComponent
	: public Component
{
public:
	RendererComponent(Entity* parent, Texture* texture);
	RendererComponent& operator=(const RendererComponent& other) = delete;
	RendererComponent(const RendererComponent& other) = delete;
	RendererComponent(RendererComponent&&) = delete;
	RendererComponent& operator=(RendererComponent&&) = delete;
	~RendererComponent();

	void Draw() const override;
private:
	Texture* m_pTexture;
	TransformComponent* m_pParentTransform;
};

