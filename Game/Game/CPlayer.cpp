#include "stdafx.h"
#include "CPlayer.h"
#include "CGamecamera.h"
#include "Camera.h"

enum {
	AnimationStand,		//立ち。
	AnimationWalk,		//歩き。
	AnimationRun,		//走り。
	AnimationJump,		//ジャンプ。
	AnimationAttack_00,	//攻撃00。
	AnimationAttack_01,	//攻撃01。
	AnimationAttack_02,	//攻撃02。
	AnimationDamage,	//ダメージ。
	AnimationDeath,		//死亡。
	NumAnimation,		//アニメーションの数。
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
	animation.SetAnimationLoopFlag(AnimationJump, false);
	animation.SetAnimationLoopFlag(AnimationAttack_00, false);
	animation.SetAnimationLoopFlag(AnimationAttack_01, false);
	animation.SetAnimationLoopFlag(AnimationAttack_02, false);
	animation.SetAnimationEndTime(AnimationAttack_00, 0.63333f);
	animation.SetAnimationEndTime(AnimationAttack_01, 0.76666f);
}

void CPlayer::Update()
{

	//移動処理
	Move();

	//アニメーション
	Animation();

	//ワールド行列の更新。
	model.Update(m_position, rotation, scale);
}

void CPlayer::Move()
{
	
	if (isAttack == false) {
		//キャラクターの移動速度を決定
		CVector3 move = m_characterController.GetMoveSpeed();
		move.x = -Pad(0).GetLStickXF() * 5.0f;
		move.z = -Pad(0).GetLStickYF() * 5.0f;

		if (m_characterController.IsJump() == false && Pad(0).IsTrigger(enButtonA)) {
			m_characterController.Jump();
			move.y = 5.0f;
		}

		//移動しているか
		if (move.x != 0.0f || move.z != 0.0f) {
			isMove = true;
		}
		else {
			isMove = false;
		}

		//決定した移動速度をキャラクターコントローラーに設定
		m_characterController.SetMoveSpeed(move);
		//キャラクターコントローラーを実行
		m_characterController.Execute();
		//実行結果を受け取る
		m_position = m_characterController.GetPosition();

		//回転させる
		CVector3 moveXZ = move;		//方向ベクトル
		moveXZ.y = 0.0f;

		//AxisZとmoveXZのなす角を求める
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
	//ジャンプアニメーション
	if (Pad(0).IsTrigger(enButtonA)) {
		animation.PlayAnimation(AnimationJump, 0.3f);
	}

	//ジャンプしていないとき
	if (m_characterController.IsJump() == false) {
		
			//攻撃アニメーション
			if (isAttack == false) {
				if (Pad(0).IsTrigger(enButtonB)) {
					//ゲームパッドの０番目のAボタンが押されたら
					attackAnimationNo = AnimationAttack_00;
					animation.PlayAnimation(AnimationAttack_00, 0.3f);
					//攻撃中のフラグをたてる
					isAttack = true;
				}
			}
			else {
				if (Pad(0).IsTrigger(enButtonB)) {
					//コンボ発生
					isCombo = true;
					//攻撃中に再度攻撃ボタンが押された
				}

				//攻撃中の処理
				if (animation.IsPlay() == false) {
					if (isCombo == true) {
						//アニメーションの再生が終了したときに
						//コンボが発生していたら
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
						//攻撃アニメーションの再生が終わったので
						//待機アニメーションを流す
						animation.PlayAnimation(AnimationStand, 0.3f);
						//攻撃フラグを下す
						isAttack = false;
						isCombo = false;
					}
				}
			}
			//走るアニメーションがループしないように
			if (isRun == false) {
				//移動している
				if (isMove == true) {
					animation.PlayAnimation(AnimationRun, 0.1f);
					isRun = true;
				}
			}
			else if (isMove == false) {
				animation.PlayAnimation(AnimationStand, 0.1f);
				isRun = false;
			}
	}
	
	//アニメーションアップデート
	animation.Update(1.0f / 60.0f);
}

void CPlayer::Render(CRenderContext& renderContext)
{
	model.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}