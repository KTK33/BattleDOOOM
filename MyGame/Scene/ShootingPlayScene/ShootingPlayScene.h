#pragma once
#include "../SceneInc.h"

//リソース読み込み専用シーン
class ShootingPlayScene :public Scene,public Menu{
public:

	ShootingPlayScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;

	bool BossArleady;
};