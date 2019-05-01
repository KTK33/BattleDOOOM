#include "Mouse.h"
#include <DxLib.h>

// �Q�[���p�b�h�̃{�^��
const int Mouse::Left{ PAD_INPUT_LEFT };
const int Mouse::Right{ PAD_INPUT_RIGHT };
const int Mouse::Middle{ PAD_INPUT_UP };

// ����̓��͏��
int Mouse::current_state_{ 0 };
// �O��̓��͏��
int Mouse::previos_state_{ 0 };

// ������
void Mouse::initialize() {
    current_state_ = 0;
    previos_state_ = 0;
}

// �X�V
void Mouse::update() {
    previos_state_ = current_state_;
    current_state_ = GetMouseInput();
}

// �}�E�X�J�[�\���̈ʒu���擾
Vector2 Mouse::cursor_point() {
    int x = 0, y = 0;
    GetMousePoint(&x, &y);
    return Vector2(float(x), float(y));
}

// �}�E�X�J�[�\���̈ʒu��ݒ�
void Mouse::cursor_point(const Vector2& point) {
    SetMousePoint(int(point.x), int(point.y));
}

// �}�E�X�J�[�\���̕\��
void Mouse::show_cursor() {
    SetMouseDispFlag(TRUE);
}

// �}�E�X�J�[�\���̔�\��
void Mouse::hide_cursor() {
    SetMouseDispFlag(FALSE);
}

// �{�^����������Ă��邩�H
bool Mouse::state(int button) {
    return (current_state_ & button) != 0;
}

// �{�^���������ꂽ���H
bool Mouse::trigger(int button) {
    return (current_state_ & ~previos_state_ & button) != 0;
}

// �{�^���������ꂽ���H
bool Mouse::release(int button) {
    return (~current_state_ & previos_state_ & button) != 0;
}

// �I������
void Mouse::finalize() {
    current_state_ = 0;
    previos_state_ = 0;
}