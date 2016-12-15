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
	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	int numObject = sizeof(enemyInfo) / sizeof(enemyInfo[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
	for (int i = 0; i < numObject; i++) {
		Enemy_00* enemy_00 = NewGO<Enemy_00>(0);
		//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
		enemy_00->Init(enemyInfo[i].modelName, enemyInfo[i].position, enemyInfo[i].rotation);
	}
}
void EnemyManager::Update()
{
}
void EnemyManager::Render(CRenderContext& renderContext)
{
}