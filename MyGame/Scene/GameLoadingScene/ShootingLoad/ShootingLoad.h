#pragma once
#include "../Scene/Scene.h"
#include "../DrawLoadScene/DrawLoadScene.h"

//リソース読み込み専用シーン
class ShootingLoad :public Scene {
public:
	ShootingLoad();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	//モデルの読み込み
	void LoadModel();
	//サウンドの読み込み
	void LoadSound();
	//画像の読み込み
	void LoadSprite();
	//エフェクトの読み込み
	void LoadEffect();

private:
	int Countres{ 0 };

	DrawLoadScene mDL;
};