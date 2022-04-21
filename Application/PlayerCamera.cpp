#include <pch.h>
#include "PlayerCamera.h"

#include <iostream>
#include <Transform.h>

#include "constants.hpp"

PlayerCamera::PlayerCamera(Transform* followTarget)
	: Camera(2.8f), m_pFollowTarget{ followTarget }
{
}

void PlayerCamera::Update(float deltaTime)
{
	// Calc actual camera size (factoring in zoom)
	Vector2f cameraSize{ Vector2f(constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT) / m_Scale };

	Vector2f targetPos = m_pFollowTarget->GetPosition();
	Vector2f newCamPos = Vector2f(
		targetPos.x - (cameraSize.x / 2),
		-cameraSize.y / 2
	);
	newCamPos.ClampX(m_LeftBoundary, m_RightBoundary);

	SetPosition(newCamPos);
}

void PlayerCamera::SetFollowTarget(Transform* target)
{
	m_pFollowTarget = target;
}
