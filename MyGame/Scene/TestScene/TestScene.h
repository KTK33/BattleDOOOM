#pragma once
#include "../SceneInc.h"

#include "../Effekseer/EffekseerEffect/EffekseerEffect.h"
#include "../Effekseer/EffectObj/EffectObj.h"


//リソース読み込み専用シーン
class TestScene :public Scene{
public:

	TestScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;

	EffectObj eff_;
};