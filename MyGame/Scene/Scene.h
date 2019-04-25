#pragma once
#include"SceneType.h"

//シーンテンプレート
class Scene {
public:
	virtual ~Scene() {}

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw()const = 0;
	//isEndがtrueになった後の処理
	virtual void end() = 0;

	virtual bool isEnd() const{ return isEnd_; }

	virtual SceneType nextScene()const { return next_; }

	//共通の初期化
	void baseInit() {
		isEnd_ = false;
	}

protected:
	bool isEnd_{ false };
	SceneType next_{ SceneType::SCENE_SHOOTING_PLAY_SCENE };
};