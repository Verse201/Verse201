#include "stdafx.h"
#include "CGamecamera.h"


CGamecamera::CGamecamera()
{
	//カメラの視点を設定
	camera.SetPosition({ 0.0f,10.0f,-10.0f });
	//カメラの注視点を設定
	camera.SetTarget({ 0.0f,0.0f,0.0f });
	//カメラの上視点を設定
	camera.SetUp({ 0.0f,1.0f,0.0f });
	//カメラ行列を計算
	camera.Update();
}

CGamecamera::~CGamecamera()
{
}

void CGamecamera::Update()
{
}