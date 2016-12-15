#include "stdafx.h"
#include "Enemy_00.h"
#include "CGamecamera.h"
#include "Camera.h"

extern CLight g_defaultLight;
extern CPlayer* g_player;

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
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルデータをロード。
	modelData.LoadModelData(filePath, &animation);
	//CSkinModelを初期化。
	model.Init(&modelData);
	//デフォルトライトを設定して。
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

	//決定した移動速度をキャラクターコントローラーに設定
	characterController.SetMoveSpeed(move);
	//キャラクターコントローラーを実行
	characterController.Execute();
	//実行結果を受け取る
	e_position = characterController.GetPosition();

	//回転させる
	CVector3 moveXZ = move_angle;		//方向ベクトル
	//moveXZ.y = 0.0f;

	//AxisZとmoveXZのなす角を求める
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

	//アニメーションアップデート
	animation.Update(1.0f / 60.0f);
	
	//ワールド行列を更新する。
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