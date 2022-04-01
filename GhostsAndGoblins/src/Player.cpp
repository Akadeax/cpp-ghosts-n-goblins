#include "pch.h"

#include <cassert>
#include <SDL.h>
#include "Player.h"
#include "Entity.h"
#include "Transform.h"
#include "AnimatorRenderer.h"

Player::Player(Entity* parent)
	: Component(parent)
{
	m_Animator = parent->GetComponent<AnimatorRenderer>();
	assert(m_Animator != nullptr && "Player has no Animator");
	m_Transform = parent->GetComponent<Transform>();
	assert(m_Transform != nullptr && "Player has no Transform");
}

void Player::Update(float deltaTime)
{
	const int MOVE_SPEED = 50;
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_A])
	{
		m_Transform->MovePosition(Vector2f(-MOVE_SPEED * deltaTime, 0));
		m_Animator->SetParameter("isWalking", true);
		m_Animator->SetFlipX(true);
	}
	else if (state[SDL_SCANCODE_D])
	{
		m_Transform->MovePosition(Vector2f(MOVE_SPEED * deltaTime, 0));
		m_Animator->SetParameter("isWalking", true);
		m_Animator->SetFlipX(false);
	}
	else
	{
		m_Animator->SetParameter("isWalking", false);
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		
		m_Transform->MovePosition(Vector2f(0, 350 * deltaTime));
	}

	m_Animator->SetParameter("isGrounded", m_Transform->GetPosition().y <= 0);
	if (m_Transform->GetPosition().y > 0)
	{
		m_Transform->MovePosition(Vector2f(0, -150 * deltaTime));
	}
}
