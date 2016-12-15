#pragma once

#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "tkEngine/character/tkCharacterController.h"
#include "CPlayer.h"

class Enemy_00: public IGameObject
{
public:
	Enemy_00();
	~Enemy_00();
	void Init(const char* modelName, CVector3 pos, CQuaternion rot);
	void Start();
	void Update();
	void Move();
	void Render(CRenderContext& renderContext);
	CVector3				e_position;			//�����ʒu
	CVector3				scale;				//�g�嗦
	CQuaternion				rotation;
	CSkinModelData			modelData;			//�X�L�����f���f�[�^
	CSkinModel				model;				//�X�L�����f��
	CAnimation				animation;
	CCharacterController	characterController;
	bool					isStand;
	CVector3				move;
	CVector3				move_angle = { 0.0f,0.0f,0.0f };
	float					angle;
};

