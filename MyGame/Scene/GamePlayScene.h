#pragma once
#include"Scene.h"
#include"../World/World.h"

//リソース読み込み専用シーン
class GamePlayScene :public Scene{
public:

	GamePlayScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

	void Pause();

private:
	World world_;

	bool PauseCheck{ false };
};