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

	void Initialize() override;
	// general draw call that applies to all renderer subclasses
	void Draw() const override final;
	// function that can be overriden for specific renderer subclass
	virtual void DrawSprite() const;

	bool GetFlipX() const;
	void SetFlipX(bool newState);
	bool GetFlipY() const;
	void SetFlipY(bool newState);

protected:
	Texture* m_pTexture;
	Transform* m_pParentTransform = nullptr;

	bool m_FlipX = false;
	bool m_FlipY = false;
};

