#pragma once
#include "../SceneInc.h"

//リソース読み込み専用シーン
class ActionPlayScene :public Scene, public Menu {
public:

	ActionPlayScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;
};