#include "SceneManager.h"
#include"Scenes.h"

//�^�C�g�����[�f�B���O�V�[������J�n
SceneManager::SceneManager() :currentScene_(SceneType::SCENE_TITLE_LOAD) {
	//���p����V�[�����쐬���A�V�[�����X�g�ɒǉ�����
	scenes_[SceneType::SCENE_TITLE_LOAD] = std::make_shared<TitleLoad>();
	scenes_[SceneType::SCENE_TITLE] = std::make_shared<GameTitleScene>();
	scenes_[SceneType::SCENE_MODESELECT] = std::make_shared<GameSelectScene>();
	scenes_[SceneType::SCENE_SHOOTING_LOAD] = std::make_shared<ShootingLoad>();
	scenes_[SceneType::SCENE_SHOOTING_PLAY] = std::make_shared<ShootingPlayScene>();
	scenes_[SceneType::SCENE_ACTION_LOAD] = std::make_shared<ActionLoad>();
	scenes_[SceneType::SCENE_ACTION_PLAY] = std::make_shared<ActionPlayScene>();
	scenes_[SceneType::SCENE_TEST] = std::make_shared<TestScene>();
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

//�V�[�����I�����Ă��邩���m�F���A�K�v�ł���Ύ��̃V�[���ɑJ�ڂ���

void SceneManager::checkIsEnd() {
	if (scenes_.at(currentScene_)->isEnd()) next();

}

//���̃V�[���֑J�ڂ���

void SceneManager::next() {
	//�V�[�����I������
	scenes_[currentScene_]->end();
	SceneType nextScene = scenes_[currentScene_]->nextScene();
	currentScene_ = nextScene;
	//���̃V�[�����J�n����
	scenes_[currentScene_]->baseInit();
	scenes_[currentScene_]->start();
}
