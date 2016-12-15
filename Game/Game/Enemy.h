#pragma once

#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"

#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/tkLight.h"

class Enemy : public IGameObject
{
public:
	//�������烁���o�֐��B
	Enemy();
	~Enemy();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);

	//�������烁���o�ϐ��B
	CSkinModel				skinModel;		//�X�L�����f���B
	CSkinModelData			skinModelData;	//�X�L�����f���f�[�^�B
	
	CVector3				e_position;
	CVector3				scale;
	CQuaternion				rotation;
	CLight					light;			//���C�g
	CCharacterController	characterController;
};