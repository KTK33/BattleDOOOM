#include "Sprite.h"
#include "../Math/MathHelper.h"
#include <cmath>
#include <DxLib.h>

// �X�v���C�g�n���h��
int Sprite::id_{ -1 };
// �X�v���C�g�f�[�^
std::unordered_map<int, AnimatedSprite> Sprite::sprite_map_;

// ������
void Sprite::initialize() {
    finalize();
}

// �摜�t�@�C���̓ǂݍ���
void Sprite::load(int id, const std::string& file_name) {
    sprite_map_[id].load(file_name);
}

// �摜�t�@�C���̓ǂݍ��� (�����w�肠��j
void Sprite::load(int id, const std::string& file_name, int row, int column) {
    sprite_map_[id].load(file_name, row, column);
}

// �o�C���h
void Sprite::bind(int id) {
    id_ = id;
}

// �`��i�摜�S�́j
void Sprite::draw(const Vector2& position) {
    sprite_map_[id_].draw(position);
}

// �`��i�摜�̂P������`��j
void Sprite::draw(const Vector2& position, int x, int y, int w, int h) {
    sprite_map_[id_].draw(position, x, y, w, h);
}

// �`��i�����ԍ��w��j
void Sprite::draw(int div_no, const Vector2& position, const Vector2& center, const Vector2& scale, float rotation) {
    sprite_map_[id_].draw(div_no, position, center, scale, rotation);
}

// �`��i�A�j���[�V�����w��j
void Sprite::draw(int animation, float time, const Vector2& position, const Vector2& center, const Vector2& scale, float rotation) {
    sprite_map_[id_].draw(animation, time, position, center, scale, rotation);
}

// �A�j���[�V�����̒ǉ�
void Sprite::add_animation(int animation, int start, int end, float time) {
    sprite_map_[id_].add_animation(animation, start, end, time);
}

// �L�[�t���[����ǉ�
void Sprite::add_key_frame(int animation, float time, int div_no) {
    sprite_map_[id_].add_key_frame(animation, time, div_no);
}

// �L�[�t���[����ǉ�
void Sprite::add_key_frame(int animation, float time, int x, int y, int w, int h) {
    sprite_map_[id_].add_key_frame(animation, time, x, y, w, h);
}

// �X�v���C�g�̍폜
void Sprite::erase(int id) {
    if (id == id_) {
        id_ = -1;
    }
    sprite_map_.erase(id);
}

// �A�j���[�V�����̏I�����Ԃ��擾
float Sprite::get_animation_end_time(int animation) {
    return sprite_map_[id_].animation_end_time(animation);
}

// �O���t�B�b�N�X�̏I������
void Sprite::finalize() {
    sprite_map_.clear();
    id_ = -1;
}

// end of file
