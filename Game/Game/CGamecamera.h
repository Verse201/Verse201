#pragma once
class CGamecamera:public IGameObject
{
public:
	CCamera camera;
	CGamecamera();
	~CGamecamera();
	void Update();
};

