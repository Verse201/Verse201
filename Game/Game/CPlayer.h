#pragma once

#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "tkEngine/character/tkCharacterController.h"

class CPlayer:public IGameObject
{
public:
	CPlayer();
	~CPlayer();
	void Start();
	void Update();
	void Render(CRenderContext& renderContext);
	void Move();
	void Animation();
	CVector3 GetPosition() {
		return m_position;
	}
	CVector3				m_position;			//�����ʒu
	CVector3				scale;				//�g�嗦
	CQuaternion				rotation;
	CSkinModelData			modelData;			//�X�L�����f���f�[�^
	CSkinModel				model;				//�X�L�����f��
	CLight					light;				//���C�g
	CAnimation				animation;			//�A�j���[�V����
	CCharacterController	m_characterController;
	int						attackAnimationNo;
	float					m_angle;
	bool					isMove;
	bool					isRun;
	bool					isAttack;
	bool					isCombo;
};

