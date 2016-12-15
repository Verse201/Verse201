#pragma once

class EnemyManager : public IGameObject {
public:
	EnemyManager();
	~EnemyManager();
	void Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
};