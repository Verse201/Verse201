#include "stdafx.h"
#include "CGamecamera.h"


CGamecamera::CGamecamera()
{
	//�J�����̎��_��ݒ�
	camera.SetPosition({ 0.0f,10.0f,-10.0f });
	//�J�����̒����_��ݒ�
	camera.SetTarget({ 0.0f,0.0f,0.0f });
	//�J�����̏㎋�_��ݒ�
	camera.SetUp({ 0.0f,1.0f,0.0f });
	//�J�����s����v�Z
	camera.Update();
}

CGamecamera::~CGamecamera()
{
}

void CGamecamera::Update()
{
}