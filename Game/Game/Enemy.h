#pragma once

#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "tkEngine/character/tkCharacterController.h"

class CEnemy:public IGameObject
{
public:
	CEnemy();
	~CEnemy();
	void Start();
	void Update();
	void Render(CRenderContext& renderContext);
	CVector3				m_position;			//立ち位置
	CVector3				scale;				//拡大率
	CQuaternion				rotation;
	CSkinModelData			modelData;			//スキンモデルデータ
	CSkinModel				model;				//スキンモデル
	CLight					light;				//ライト
};

