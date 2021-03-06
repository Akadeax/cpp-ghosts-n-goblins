#include "pch.h"

#include <cassert>
#include <InputHandler.h>
#include <Entity.h>
#include <Scene.h>
#include <Game.h>
#include <Transform.h>
#include <PhysicsBody.h>
#include <Collider.h>
#include <PhysicsHandler.h>
#include <AnimatorRenderer.h>
#include <utils.h>

#include "Player.h"

Player::Player(Entity* parent)
	: Component(parent)
{
}

void Player::Initialize()
{
	m_pTransform = m_pParent->GetComponent<Transform>();
	assert(m_pTransform != nullptr && "Player has no transform");
	m_pPhysicsBody = m_pParent->GetComponent<PhysicsBody>();
	assert(m_pPhysicsBody != nullptr && "Player has no physics body");
	m_pAnimator = m_pParent->GetComponent<AnimatorRenderer>();
	assert(m_pAnimator != nullptr && "Player has no animator");
	m_pCollider = m_pParent->GetComponent<Collider>();
	assert(m_pCollider != nullptr && "Player has no collider");

	m_pCollider->SetBaseVertices(std::vector<Vector2f>{
		Vector2f(-m_ColliderWidth / 2, -m_ColliderHeight / 2),
		Vector2f(-m_ColliderWidth / 2, m_ColliderHeight / 2),
		Vector2f(m_ColliderWidth / 2, m_ColliderHeight / 2),
		Vector2f(m_ColliderWidth / 2, -m_ColliderHeight / 2)
	});
}

void Player::Update(float deltaTime)
{
	UpdateMovement();
	CheckGrounded();

	if (!m_IsGrounded)
	{
		// Apply gravity if we're not grounded
		m_pPhysicsBody->AddVelocity(Vector2f(0, -1 * m_GravityFactor));
	}
	else
	{
		// Reset velocity, otherwise gravity pulls into the ground
		// if we'd reset to 0 the ground wouldn't register collision
		m_pPhysicsBody->SetYVelocity(-5);
	}

	UpdateJump();
	UpdateShooting();
}

void Player::Draw() const
{
	Vector2f currPos{ m_pTransform->GetPosition() };
	Vector2f pA{ currPos + Vector2f(-m_GroundedCheckXSize / 2, m_GroundedCheckYOffset)};
	Vector2f pB{ currPos + Vector2f(m_GroundedCheckXSize / 2, m_GroundedCheckYOffset)};
	utils::DrawLine(pA.ToPoint2f(), pB.ToPoint2f());
}

void Player::UpdateMovement()
{
	InputHandler* input = m_pParent->GetScene()->GetGame()->GetInputHandler();

	if (input->GetKeyPressed("move_left"))
	{
		m_CurrentLookDir = -1;
		if (m_IsGrounded)
		{
			m_CurrentMoveDir = -1;
			m_pAnimator->SetParameter("isWalking", true);
		}
	}
	else if (input->GetKeyPressed("move_right"))
	{
		m_CurrentLookDir = 1;
		if (m_IsGrounded)
		{
			m_CurrentMoveDir = 1;
			m_pAnimator->SetParameter("isWalking", true);
		}
	}
	else
	{
		if (m_IsGrounded)
		{
			m_CurrentMoveDir = 0;
			m_pAnimator->SetParameter("isWalking", false);
		}
	}


	// Crouching
	m_IsCrouching = input->GetKeyPressed("crouch") && m_IsGrounded;
	m_pAnimator->SetParameter("isCrouching", m_IsCrouching);

	if (m_IsCrouching)
	{
		m_CurrentMoveDir = 0;

		// set shortened collider
		m_pCollider->SetBaseVertices(std::vector<Vector2f>{
			Vector2f(-m_ColliderWidth / 2, -m_ColliderHeight / 2),
			Vector2f(-m_ColliderWidth / 2, -m_ColliderHeight / 2 + m_ColliderHeight * m_CrouchShortenFactor),
			Vector2f(m_ColliderWidth / 2, -m_ColliderHeight / 2 + m_ColliderHeight * m_CrouchShortenFactor),
			Vector2f(m_ColliderWidth / 2, -m_ColliderHeight / 2)
		});
	}
	else
	{
		// set back to normal collider
		m_pCollider->SetBaseVertices(std::vector<Vector2f>{
			Vector2f(-m_ColliderWidth / 2, -m_ColliderHeight / 2),
			Vector2f(-m_ColliderWidth / 2, m_ColliderHeight / 2),
			Vector2f(m_ColliderWidth / 2, m_ColliderHeight / 2),
			Vector2f(m_ColliderWidth / 2, -m_ColliderHeight / 2)
		});
	}



	m_pPhysicsBody->SetXVelocity(m_MoveSpeed * m_CurrentMoveDir);
	m_pAnimator->SetFlipX(m_CurrentLookDir == -1);
}

void Player::CheckGrounded()
{
	Vector2f playerPos = m_pPhysicsBody->GetTransform()->GetPosition();
	// Offset both ground check points down and to the left/right according to consts
	// If Any ground object is between these two points, player is grounded
	Vector2f castBottomLeft = playerPos + Vector2f(-(m_GroundedCheckXSize / 2), m_GroundedCheckYOffset);
	Vector2f castBottomRight = playerPos + Vector2f(m_GroundedCheckXSize / 2, m_GroundedCheckYOffset);

	std::pair<bool, Collider*> groundedResult = GetPhysicsHandler()->Linecast(castBottomLeft, castBottomRight, "ground");
	m_IsGrounded = groundedResult.first && !groundedResult.second->IsTrigger();

	m_pAnimator->SetParameter("isGrounded", m_IsGrounded);
}

void Player::UpdateJump()
{
	InputHandler* input = m_pParent->GetScene()->GetGame()->GetInputHandler();
	if (input->GetKeyDown("jump") && m_IsGrounded)
	{
		m_pPhysicsBody->SetYVelocity(m_JumpStrength);
	}
}

void Player::UpdateShooting()
{
}

