#include "stdafx.h"
#include "Enemy_00.h"
#include "CGamecamera.h"
#include "Camera.h"

extern CLight g_defaultLight;
extern CPlayer* g_player;

enum {
	AnimationStand,		//�����B
	AnimationWalk,		//�����B
	AnimationRun,		//����B
	AnimationJump,		//�W�����v�B
	AnimationAttack_00,	//�U��00�B
	AnimationAttack_01,	//�U��01�B
	AnimationAttack_02,	//�U��02�B
	AnimationDamage,	//�_���[�W�B
	AnimationDeath,		//���S�B
	NumAnimation,		//�A�j���[�V�����̐��B
};

Enemy_00::Enemy_00()
{
}

Enemy_00::~Enemy_00()
{
}

void Enemy_00::Start()
{
}

void Enemy_00::Init(const char* modelName, CVector3 pos, CQuaternion rot)
{
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//���f���f�[�^�����[�h�B
	modelData.LoadModelData(filePath, &animation);
	//CSkinModel���������B
	model.Init(&modelData);
	//�f�t�H���g���C�g��ݒ肵�āB
	model.SetLight(&g_defaultLight);
	model.SetShadowCasterFlag(true);
	model.SetShadowReceiverFlag(true);

	e_position = pos;
	rotation = rot;
	scale = { 2.0f,2.0f,2.0f };

	characterController.Init(0.6f, 1.0f, e_position);
	characterController.SetGravity(-18.8f);

	animation.PlayAnimation(AnimationWalk);
}

void Enemy_00::Update()
{	
	move = characterController.GetMoveSpeed();


	Move();

	//���肵���ړ����x���L�����N�^�[�R���g���[���[�ɐݒ�
	characterController.SetMoveSpeed(move);
	//�L�����N�^�[�R���g���[���[�����s
	characterController.Execute();
	//���s���ʂ��󂯎��
	e_position = characterController.GetPosition();

	//��]������
	CVector3 moveXZ = move_angle;		//�����x�N�g��
	//moveXZ.y = 0.0f;

	//AxisZ��moveXZ�̂Ȃ��p�����߂�
	if (moveXZ.Length() > 0.0f)
	{
		angle = moveXZ.Dot(CVector3::AxisZ);
		angle /= (moveXZ.Length() + 0.0001f);
		angle = acosf(angle);
		angle = angle * 180.0 / CMath::PI;

		if (moveXZ.x < 0.0f)
		{
			angle *= -1.0f;
		}
	}
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(angle));

	//�A�j���[�V�����A�b�v�f�[�g
	animation.Update(1.0f / 60.0f);
	
	//���[���h�s����X�V����B
	model.Update(e_position, rotation, scale);
}

void Enemy_00::Move()
{
	CVector3 diff, p_position;
	p_position = g_player->GetPosition();
	diff.x = p_position.x - e_position.x;
	diff.y = p_position.y - e_position.y;
	diff.z = p_position.z - e_position.z;
	if (diff.Length() > 0.0f) {
		float length = diff.Length();
		diff.x /= length;
		diff.y /= length;
		diff.z /= length;
		move_angle.x = diff.x * 0.005f;
		move_angle.y = diff.y * 0.005f;
		move_angle.z = diff.z * 0.005f;
	}
}

void Enemy_00::Render(CRenderContext& renderContext)
{
	model.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}