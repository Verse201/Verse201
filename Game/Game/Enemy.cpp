#include "stdafx.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Start()
{
	modelData.LoadModelData("Assets/modelData/Player.X", NULL);
	model.Init(&modelData);
	light.SetAmbinetLight({ 1.0f,1.0f,1.0f });
	model.SetLight(&light);
}

void CEnemy::Update()
{
}

void CEnemy::Render(CRenderContext& renderContext)
{
}