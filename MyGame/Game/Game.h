#ifndef GAME_H_
#define GAME_H_

#include "../Scene/SceneManager.h"
#include "Define.h"

// main�֐����G���g���|�C���g�ɂ���
#pragma comment(linker, "/entry:mainCRTStartup")

// �Q�[���N���X
class Game {
public:
    // �R���X�g���N�^
    Game(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, bool full_screen = false,float fps = 60.0f);
    // ���s
    int run();
    // �R�s�[�֎~
    Game(const Game& other) = delete;
    Game& operator = (const Game& other) = delete;

private:
    // �J�n
    virtual void start();
    // �X�V
    virtual void update(float);
    // �`��
    virtual void draw();
	//�t���[���I��������
	void frameEnd();
    // �I��
    virtual void end();
    // ���s�����H
    virtual bool is_running() const;

private:
    // �E�B���h�E�̕�
    int window_width_{ WINDOW_WIDTH };
    // �E�B���h�E�̍���
    int window_height_{ WINDOW_HEIGHT };
    // �t���X�N���[�����[�h
    bool is_full_screen_{ false };

	SceneManager sceneManager_;

	// FPS
	float mFps;
};

#endif
