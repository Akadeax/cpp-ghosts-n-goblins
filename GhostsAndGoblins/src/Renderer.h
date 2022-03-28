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
	~Renderer();

	void Draw() const override;
private:
	Texture* m_pTexture;
	Transform* m_pParentTransform;
};

