#include "Game.h"
#include <DxLib.h>

#include "../Input/GamePad.h"
#include "../Input/Mouse.h"
#include "../Math/Random.h"
#include "../Graphics/Graphics2D.h"
#include "../Sound/Sound.h"
#include "../Graphics/Graphics3D.h"
#include "FpsSetting.h"
#include "Time.h"

// コンストラクタ
Game::Game(int width, int height, bool full_screen,float fps) :
    window_width_{ width },
    window_height_{ height },
	is_full_screen_{ full_screen },
	mFps{fps}
{}

	// 実行
int Game::run() {
    SetWindowSize(window_width_, window_height_);
    // フルスクリーンモード時の解像度を設定
    SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);
    // グラフィックモードの設定
    SetGraphMode(window_width_, window_height_, 32);
	// 描画倍率
	SetWindowSizeExtendRate(1.0f);
    // ウインドウモードか
    ChangeWindowMode(is_full_screen_ ? FALSE : TRUE);
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	SetWindowSizeExtendRate(0.6f);
    // ＤＸライブラリの初期化
    DxLib_Init();
    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);
    // 乱数の初期化
    Random::randomize();
    // 2Dグラフィックの初期化
    Graphics2D::initialize();
    // サウンドの初期化
	Sound::GetInstance().Initialize();
    // ゲームパッドの初期化
	
    // マウスの初期化
    Mouse::initialize();
    // 3Dグラフィックスの初期化
    Graphics3D::initialize();

	Fps fps;

    // 開始
    start();

	fps.initialize();

    // メインループ(何かキーが押されたらループを抜ける)
    while (ProcessMessage() == 0 && is_running()) {
		Time::GetInstance().update();
        // 更新
        update(1.0f);
		fps.update();
        // 画面のクリア
        ClearDrawScreen();
        // 描画
        draw();

		frameEnd();
		Time::GetInstance().draw_fps();
        // 裏画面の内容を表画面に反映
        ScreenFlip();
		fps.Wait();
    }
    // 終了
    end();
    // パッドの終了処理
    //GamePad::finalize();
    // マウスの終了処理
    Mouse::finalize();
    // サウンドの終了処理
	//Sound::GetInstance().
    // ３Ｄグラフィックの後始末 
    //Graphics3D::finalize();
    // 2Dグラフィックの終了処理
    Graphics2D::finalize();
    // ＤＸライブラリの後始末
    DxLib_End();
    // 正常終了
    return 0;
}

// 開始
void Game::start() {
	sceneManager_.start();
}

// 更新
void Game::update(float) {
	// ゲームパッドの更新
	GamePad::GetInstance().Update();
	// マウスの更新
	Mouse::update();
	sceneManager_.update(60.0f / 60.0f);
}

// 描画
void Game::draw() {
	sceneManager_.draw();
}

//フレーム終了時処理
void Game::frameEnd() {
	sceneManager_.checkIsEnd();
}
// 終了
void Game::end() {
}

// 実行中か？
bool Game::is_running() const {
    // エスケープキーで強制終了
    return CheckHitKey(KEY_INPUT_ESCAPE) == 0;
}



// end of file
