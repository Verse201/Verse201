#pragma once

#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"

#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/tkLight.h"

class Enemy : public IGameObject
{
public:
	//ここからメンバ関数。
	Enemy();
	~Enemy();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);

	//ここからメンバ変数。
	CSkinModel				skinModel;		//スキンモデル。
	CSkinModelData			skinModelData;	//スキンモデルデータ。
	
	CVector3				e_position;
	CVector3				scale;
	CQuaternion				rotation;
	CLight					light;			//ライト
	CCharacterController	characterController;
};