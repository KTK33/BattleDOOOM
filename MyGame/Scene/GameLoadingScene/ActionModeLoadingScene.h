#pragma once
#include"../Scene.h"

//リソース読み込み専用シーン
class ActionModeLoadingScene :public Scene {
public:
	ActionModeLoadingScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	//モデルの読み込み
	void LoadModel();
	//色々読み込み
	void LoadAny();
	//シェーダーの読み込み
	void LoadShader();
	//サウンドの読み込み
	void LoadSound();
	//画像の読み込み
	void LoadSprite();

private:
	int Countres{ 0 };
};