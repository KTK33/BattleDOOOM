#ifndef GAME_PAD_H_
#define GAME_PAD_H_

// �Q�[���p�b�h�N���X
class GamePad {
public:
    // �Q�[���p�b�h�̃{�^��
    static const int Left;
    static const int Right;
    static const int Up;
    static const int Down;
    static const int A;
    static const int B;
    static const int X;
    static const int Y;
    static const int Back;
    static const int Start;
	static const int RightButton;
	static const int LeftButton;
	static const int RightTrigger;

    // ������
    static void initialize();
    // �X�V
    static void update();
    // �{�^����������Ă��邩�H
    static bool state(int button);
    // �{�^���������ꂽ���H
    static bool trigger(int button);
    // �{�^���������ꂽ���H
    static bool release(int button);
    // �I������
    static void finalize();

private:
    // ����̓��͏��
    static int current_state_;
    // �O��̓��͏��
    static int previos_state_;
};

#endif

// end of file
