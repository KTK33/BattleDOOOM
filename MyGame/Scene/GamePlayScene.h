#pragma once
#include"Scene.h"
#include"../World/World.h"
#include "Menu.h"

//リソース読み込み専用シーン
class GamePlayScene :public Scene,public Menu{
public:

	GamePlayScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;

	bool BossArleady;
};