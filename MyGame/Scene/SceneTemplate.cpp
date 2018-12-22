#include "SceneTemplate.h"

//コンストラクタ(定数の設定等はここで行う、初期化並びを利用して必ず変数を1度初期化する事)

SceneTemplate::SceneTemplate() {
	//シーンはデフォルトでisEnd(bool)とnext_(SceneType)を持っている
	//next_の遷移先は必ず値を設定する事
	//例) next_=SceneType::SCENE_GAMEPLAY;
}

//デストラクタ(コンテナの後始末等、ゲーム終了時に必要な処理はここで行う)

SceneTemplate::~SceneTemplate() {

}

//シーン開始時に呼び出される(world作成、値の初期化等はここで行う)

void SceneTemplate::start() {

}

//毎フレーム呼び出される(キャラクターやworldの更新等はここで行う)

void SceneTemplate::update(float deltaTime) {

}

//毎フレームupdateの後に呼び出される(描画はここで行う、constなため、draw内でグローバル変数の値を変更したりは出来ない)

void SceneTemplate::draw() const {

}

//シーンのisEnd_フラグがtrueになった時に呼び出される(シーン終了時の処理はここで行う)

void SceneTemplate::end() {

}
