#include "stdafx.h"
#include "Camera.h"
#include "CPlayer.h"

Camera* g_gameCamera;
extern CPlayer* g_player;

Camera::Camera()
{ 
	m_position = CVector3::Zero;
}

Camera::~Camera()
{
}

void Camera::Start()
{
	//ŽÎ‚ßã‚©‚çŒ©‰º‚ë‚·Š´‚¶‚ÌƒJƒƒ‰‚É‚·‚é
	m_camera.SetPosition({ 0.0f, 1.0f, 16.0f });
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
}

void Camera::Update()
{
	Cposition = m_camera.GetPosition();
	Pposition = g_player->GetPosition();
	
	Cposition.x = Pposition.x;
	Cposition.y = Pposition.y + 3.0f;
	Cposition.z = Pposition.z + 10.0f;

	m_camera.SetPosition(Cposition);
	m_camera.SetTarget(Pposition);
	m_camera.Update();
}