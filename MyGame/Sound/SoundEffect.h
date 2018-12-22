#ifndef SOUND_EFFECT_H_
#define SOUND_EFFECT_H_

#include <string>
#include <unordered_map>

// ���ʉ��N���X
class SoundEffect {
public:
    // ������
    static void initialize();
    // �I������
    static void finalize();
    // �ǂݍ���
    static bool load(int id, const std::string& file_name);
    // �폜
    static void erase(int id);
    // �o�C���h
    static void bind(int id);
    // ���ʉ��̍Đ�
    static void play();
private:
    // �o�C���h����SE
    static int se_;
    // SE�n���h��
    static std::unordered_map<int, int> se_map_;
};

#endif
