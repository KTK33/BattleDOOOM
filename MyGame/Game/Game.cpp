#include "Game.h"
#include <DxLib.h>

#include "../Input/GamePad/GamePad.h"
#include "../Input/KeyBoard/Keyboard.h"
#include "../Input/Mouse/Mouse.h"
#include "../Math/Random.h"
#include "../Graphics/Graphics2D.h"
#include "../Sound/Sound.h"
#include "../Graphics/Graphics3D.h"
#include "FpsSetting.h"
#include "Time.h"

// �R���X�g���N�^
Game::Game(int width, int height, bool full_screen,float fps) :
    window_width_{ width },
    window_height_{ height },
	is_full_screen_{ full_screen },
	mFps{fps}
{}

	// ���s
int Game::run() {
	SetMainWindowText("BattleDOOOM");
    SetWindowSize(window_width_, window_height_);
    // �t���X�N���[�����[�h���̉𑜓x��ݒ�
    SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);
    // �O���t�B�b�N���[�h�̐ݒ�
    SetGraphMode(window_width_, window_height_, 32);
	// �`��{��
	SetWindowSizeExtendRate(1.0f);
    // �E�C���h�E���[�h��
    ChangeWindowMode(is_full_screen_ ? FALSE : TRUE);
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	SetWindowSizeExtendRate(0.6f);
    // �c�w���C�u�����̏�����
    DxLib_Init();
    // �`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);
    // �����̏�����
    Random::randomize();
    // 2D�O���t�B�b�N�̏�����
    Graphics2D::initialize();
    // �T�E���h�̏�����
	Sound::GetInstance().Initialize();
    // �Q�[���p�b�h�̏�����
	
    // �}�E�X�̏�����
    Mouse::initialize();
    // 3D�O���t�B�b�N�X�̏�����
    Graphics3D::initialize();

	Fps fps;

    // �J�n
    start();

	fps.initialize();

    // ���C�����[�v(�����L�[�������ꂽ�烋�[�v�𔲂���)
    while (ProcessMessage() == 0 && is_running() && is_runningPad()) {
		Time::GetInstance().update();
        // �X�V
        update(1.0f);
		fps.update();
        // ��ʂ̃N���A
        ClearDrawScreen();
        // �`��
        draw();

		frameEnd();
		Time::GetInstance().draw_fps();
        // ����ʂ̓��e��\��ʂɔ��f
        ScreenFlip();
		fps.Wait();
    }
    // �I��
    end();
    // �p�b�h�̏I������
    //GamePad::finalize();
    // �}�E�X�̏I������
    Mouse::finalize();
    // �T�E���h�̏I������
	//Sound::GetInstance().
    // �R�c�O���t�B�b�N�̌�n�� 
    //Graphics3D::finalize();
    // 2D�O���t�B�b�N�̏I������
    Graphics2D::finalize();
    // �c�w���C�u�����̌�n��
    DxLib_End();
    // ����I��
    return 0;
}

// �J�n
void Game::start() {
	sceneManager_.start();
}

// �X�V
void Game::update(float) {
	// �Q�[���p�b�h�̍X�V
	GamePad::GetInstance().Update();
	Keyboard::GetInstance().Update();
	// �}�E�X�̍X�V
	Mouse::update();
	sceneManager_.update(60.0f / 60.0f);
}

// �`��
void Game::draw() {
	sceneManager_.draw();
}

//�t���[���I��������
void Game::frameEnd() {
	sceneManager_.checkIsEnd();
}
// �I��
void Game::end() {
}

// ���s�����H
bool Game::is_running() const {
    // �G�X�P�[�v�L�[�ŋ����I��
    return CheckHitKey(KEY_INPUT_ESCAPE) == 0;
}

bool Game::is_runningPad() const{
	return GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM7) == 0;
}



// end of file
