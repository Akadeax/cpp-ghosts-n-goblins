#pragma once
#include "Entity.h"

class Texture;
class Transform;

class Renderer
	: public Component
{
public:
	Renderer(Entity* parent, Texture* texture);
	Renderer& operator=(const Renderer& other) = delete;
	Renderer(const Renderer& other) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;
	virtual ~Renderer();

	virtual void Draw() const override;

protected:
	Texture* m_pTexture;
	Transform* m_pParentTransform;
};

