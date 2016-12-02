#pragma once
#include "CPlayer.h"

class Camera : public IGameObject
{
public:

	Camera();
	~Camera();
	void Start();
	void Update();
	const CMatrix& GetViewMatrix() const
	{
		return m_camera.GetViewMatrix();
	}
	const CMatrix& GetProjectionMatrix() const
	{
		return m_camera.GetProjectionMatrix();
	}
	CVector3 Cposition;
	CVector3 Pposition;
	CCharacterController	m_characterController;
private:
	CCamera					m_camera;	//カメラ。
	CVector3				m_position; //座標。

	const	CVector3		m_def_pos = { 0.0f,2.0f,5.0f };
};

extern Camera* g_gameCamera;

