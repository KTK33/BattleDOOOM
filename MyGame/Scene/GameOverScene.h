#pragma once
#include"Scene.h"
#include"../World/World.h"

//リソース読み込み専用シーン
class GameOrverScene :public Scene {
public:

	GameOrverScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;
};