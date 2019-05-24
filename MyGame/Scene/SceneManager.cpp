#include "SceneManager.h"
#include"Scenes.h"

//タイトルローディングシーンから開始
SceneManager::SceneManager() :currentScene_(SceneType::SCENE_TITLE_LOAD) {
	//利用するシーンを作成し、シーンリストに追加する
	scenes_[SceneType::SCENE_TITLE_LOAD] = std::make_shared<TitleLoad>();
	scenes_[SceneType::SCENE_TITLE] = std::make_shared<GameTitleScene>();
	scenes_[SceneType::SCENE_MODESELECT] = std::make_shared<GameSelectScene>();
	scenes_[SceneType::SCENE_SHOOTING_LOAD] = std::make_shared<ShootingLoad>();
	scenes_[SceneType::SCENE_SHOOTING_PLAY] = std::make_shared<ShootingPlayScene>();
	scenes_[SceneType::SCENE_ACTION_LOAD] = std::make_shared<ActionLoad>();
	scenes_[SceneType::SCENE_ACTION_PLAY] = std::make_shared<ActionPlayScene>();
}

SceneManager::~SceneManager() {
	scenes_.clear();
}

void SceneManager::start() {
	scenes_[currentScene_]->start();
}

void SceneManager::update(float deltaTime) {
	scenes_[currentScene_]->update(deltaTime);
}

void SceneManager::draw() {
	scenes_[currentScene_]->draw();
}

//シーンが終了しているかを確認し、必要であれば次のシーンに遷移する

void SceneManager::checkIsEnd() {
	if (scenes_.at(currentScene_)->isEnd()) next();

}

//次のシーンへ遷移する

void SceneManager::next() {
	//シーンを終了して
	scenes_[currentScene_]->end();
	SceneType nextScene = scenes_[currentScene_]->nextScene();
	currentScene_ = nextScene;
	//次のシーンを開始する
	scenes_[currentScene_]->baseInit();
	scenes_[currentScene_]->start();
}
