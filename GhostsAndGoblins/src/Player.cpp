#include "pch.h"

#include <cassert>
#include <SDL.h>
#include "Player.h"
#include "Entity.h"
#include "Transform.h"
#include "PhysicsBody.h"
#include "AnimatorRenderer.h"
#include "Collider.h"
#include "PhysicsHandler.h"
#include "utils.h"
#include "collisions.h"
#include "InputHandler.h"

Player::Player(Entity* entity)
	: Component(entity)
{
}

void Player::Initialize()
{
	m_Animator = m_pParent->GetComponent<AnimatorRenderer>();
	assert(m_Animator != nullptr && "Player has no Animator");
	m_Transform = m_pParent->GetComponent<Transform>();
	assert(m_Transform != nullptr && "Player has no Transform");
	m_PhysicsBody = m_pParent->GetComponent<PhysicsBody>();
	assert(m_PhysicsBody != nullptr && "Player has no physics body");
}

void Player::Update(float deltaTime)
{
	if (GetParent()->GetInputHandler()->GetKeyPressed(InputHandler::Input::WalkLeft))
	{
		m_Animator->SetFlipX(true);
		m_Animator->SetParameter("isWalking", true);
		if (m_IsGrounded)
		m_PhysicsBody->SetXVelocity(-m_MoveSpeed);
	}
	else if (GetParent()->GetInputHandler()->GetKeyPressed(InputHandler::Input::WalkRight))
	{
		m_Animator->SetFlipX(false);
		m_Animator->SetParameter("isWalking", true);
		if(m_IsGrounded)
		m_PhysicsBody->SetXVelocity(m_MoveSpeed);
	}
	else if(m_IsGrounded)
	{
		m_PhysicsBody->SetXVelocity(0);
		m_Animator->SetParameter("isWalking", false);
	}

	// Jump
	if (GetParent()->GetInputHandler()->GetKeyDown(InputHandler::Input::Jump) && m_IsGrounded)
	{
		m_PhysicsBody->AddVelocity(Vector2f(0, m_JumpStrength));
	}

	// Apply gravity
	if (!m_IsGrounded)
	{
		m_PhysicsBody->AddVelocity(Vector2f(0, -6 * m_GravityFactor));
	}


	// Grounded
	Vector2f playerPos = m_PhysicsBody->GetTransform()->GetPosition();
	// Offset both ground check points down and to the left/right according to consts
	// If Anything is between these two points, player is grounded
	Vector2f castBottomLeft = playerPos + Vector2f(-(GROUNDED_CHECK_X_SIZE / 2), GROUNDED_CHECK_Y_OFFSET);
	Vector2f castBottomRight = playerPos + Vector2f(GROUNDED_CHECK_X_SIZE / 2, GROUNDED_CHECK_Y_OFFSET);

	std::pair<bool, Collider*> groundedResult = GetPhysicsHandler()->Linecast(castBottomLeft, castBottomRight);
	m_IsGrounded = groundedResult.first && !groundedResult.second->IsTrigger();
	m_Animator->SetParameter("isGrounded", m_IsGrounded);
}

void Player::Draw() const
{
	Transform* trans = m_PhysicsBody->GetTransform();
	collisions::LineLine(
	Vector2f(
		-(GROUNDED_CHECK_X_SIZE / 2),
		GROUNDED_CHECK_Y_OFFSET
	), 
	Vector2f(
		GROUNDED_CHECK_X_SIZE / 2,
		GROUNDED_CHECK_Y_OFFSET
	), Vector2f(), Vector2f());
}
