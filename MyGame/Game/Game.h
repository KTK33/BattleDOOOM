#ifndef GAME_H_
#define GAME_H_

#include "../Scene/SceneManager.h"
#include "Define.h"

// main関数をエントリポイントにする
#pragma comment(linker, "/entry:mainCRTStartup")

// ゲームクラス
class Game {
public:
    // コンストラクタ
    Game(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, bool full_screen = false,float fps = 60.0f);
    // 実行
    int run();
    // コピー禁止
    Game(const Game& other) = delete;
    Game& operator = (const Game& other) = delete;

private:
    // 開始
    virtual void start();
    // 更新
    virtual void update(float);
    // 描画
    virtual void draw();
	//フレーム終了時処理
	void frameEnd();
    // 終了
    virtual void end();
    // 実行中か？
    virtual bool is_running() const;
	virtual bool is_runningPad() const;

private:
    // ウィンドウの幅
    int window_width_{ WINDOW_WIDTH };
    // ウィンドウの高さ
    int window_height_{ WINDOW_HEIGHT };
    // フルスクリーンモード
    bool is_full_screen_{ false };

	SceneManager sceneManager_;

	// FPS
	float mFps;
};

#endif
