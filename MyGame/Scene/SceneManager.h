#pragma once
#include<map>
#include<memory>
#include"SceneType.h"
class Scene;

//シーンの管理を行う、Game及びその派生クラスで利用する
class SceneManager {
public:
	SceneManager();
	~SceneManager();
	void start();
	void update(float deltaTime);
	void draw();
	//シーンが終了しているかを確認し、必要であれば次のシーンに遷移する
	void checkIsEnd();
	//次のシーンへ遷移する
	void next();


private:
	//シーン一覧
	std::map<SceneType, std::shared_ptr<Scene>> scenes_;
	//現在のシーン
	SceneType currentScene_;
};