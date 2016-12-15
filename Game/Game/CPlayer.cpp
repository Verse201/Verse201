#include "stdafx.h"
#include "CPlayer.h"
#include "CGamecamera.h"
#include "Camera.h"

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

CPlayer::CPlayer()
{
	isMove = false;
	isRun = false;
	isAttack = false;
	isCombo = false;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	modelData.LoadModelData("Assets/modelData/Player.X", &animation);
	model.Init(&modelData);
	light.SetAmbinetLight({ 1.0f,1.0f,1.0f });
	model.SetLight(&light);
	m_position = { 0.0f,0.0f,0.0f };
	scale = { 2.5f, 2.5f, 2.5f };
	rotation = { 0.0f,0.0f,0.0f,1.0f };
	m_angle = 0.0f;
	m_characterController.Init(0.5f, 1.0f, m_position);
	
	animation.PlayAnimation(AnimationStand);
	animation.SetAnimationLoopFlag(AnimationAttack_00, false);
	animation.SetAnimationLoopFlag(AnimationAttack_01, false);
	animation.SetAnimationLoopFlag(AnimationAttack_02, false);
	animation.SetAnimationEndTime(AnimationAttack_00, 0.63333f);
	animation.SetAnimationEndTime(AnimationAttack_01, 0.76666f);
}

void CPlayer::Update()
{

	//�ړ�����
	Move();

	//�A�j���[�V����
	Animation();

	//���[���h�s��̍X�V�B
	model.Update(m_position, rotation, scale);
}

void CPlayer::Move()
{
	
	if (isAttack == false) {
		//�L�����N�^�[�̈ړ����x������
		CVector3 move = m_characterController.GetMoveSpeed();
		move.x = -Pad(0).GetLStickXF() * 10.0f;
		move.z = -Pad(0).GetLStickYF() * 10.0f;

		//�ړ����Ă��邩
		if (move.x != 0.0f || move.z != 0.0f) {
			isMove = true;
		}
		else {
			isMove = false;
		}

		//���肵���ړ����x���L�����N�^�[�R���g���[���[�ɐݒ�
		m_characterController.SetMoveSpeed(move);
		//�L�����N�^�[�R���g���[���[�����s
		m_characterController.Execute();
		//���s���ʂ��󂯎��
		m_position = m_characterController.GetPosition();

		//��]������
		CVector3 moveXZ = move;		//�����x�N�g��
		moveXZ.y = 0.0f;

		//AxisZ��moveXZ�̂Ȃ��p�����߂�
		if (moveXZ.Length() > 0.0f)
		{
			m_angle = moveXZ.Dot(CVector3::AxisZ);
			m_angle /= (moveXZ.Length() + 0.0001f);
			m_angle = acosf(m_angle);
			m_angle = m_angle * 180.0 / CMath::PI;

			if (moveXZ.x < 0.0f)
			{
				m_angle *= -1.0f;
			}
		}
		rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(m_angle));
	}
}

void CPlayer::Animation()
{
	//����A�j���[�V����
	if (isRun == false) {
		if (isMove == true) {
			animation.PlayAnimation(AnimationRun, 0.1f);
			isRun = true;
		}
	}
	else if (isMove == false) {
		animation.PlayAnimation(AnimationStand, 0.1f);
		isRun = false;
	}
	
	//�U���A�j���[�V����
	if (isAttack == false) {
		if (Pad(0).IsTrigger(enButtonB)) {
			//�Q�[���p�b�h�̂O�Ԗڂ�A�{�^���������ꂽ��
			attackAnimationNo = AnimationAttack_00;
			animation.PlayAnimation(AnimationAttack_00, 0.3f);
			//�U�����̃t���O�����Ă�
			isAttack = true;
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonB)) {
			//�R���{����
			isCombo = true;
			//�U�����ɍēx�U���{�^���������ꂽ
		}

		//�U�����̏���
		if (animation.IsPlay() == false) {
			if (isCombo == true) {
			//�A�j���[�V�����̍Đ����I�������Ƃ���
			//�R���{���������Ă�����
				if (attackAnimationNo == AnimationAttack_00) {
					animation.PlayAnimation(AnimationAttack_01, 0.3f);
					attackAnimationNo = AnimationAttack_01;
				}
				else if (attackAnimationNo == AnimationAttack_01) {
					animation.PlayAnimation(AnimationAttack_02, 0.3f);
					attackAnimationNo = AnimationAttack_02;
				}
				isCombo = false;
			}
			else {
				//�U���A�j���[�V�����̍Đ����I������̂�
				//�ҋ@�A�j���[�V�����𗬂�
				animation.PlayAnimation(AnimationStand, 0.3f);
				//�U���t���O������
				isAttack = false;
				isCombo = false;
				isRun = false;
			}
		}
	}

	
	//�A�j���[�V�����A�b�v�f�[�g
	animation.Update(1.0f / 60.0f);
}

void CPlayer::Render(CRenderContext& renderContext)
{
	model.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}