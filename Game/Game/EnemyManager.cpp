#include "stdafx.h"
#include "Enemy_00.h"
#include "EnemyManager.h"

struct EnemyInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

EnemyInfo enemyInfo[] = {
#include "EnemyInfo.h"
};

EnemyManager::EnemyManager()
{
}
EnemyManager::~EnemyManager()
{
}
void EnemyManager::Start()
{	
	//マップにいくつのオブジェクトが配置されているか調べる。
	int numObject = sizeof(enemyInfo) / sizeof(enemyInfo[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; i < numObject; i++) {
		Enemy_00* enemy_00 = NewGO<Enemy_00>(0);
		//モデル名、座標、回転を与えてマップチップを初期化する。
		enemy_00->Init(enemyInfo[i].modelName, enemyInfo[i].position, enemyInfo[i].rotation);
	}
}
void EnemyManager::Update()
{
}
void EnemyManager::Render(CRenderContext& renderContext)
{
}