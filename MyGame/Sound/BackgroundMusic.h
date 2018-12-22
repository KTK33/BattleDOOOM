#ifndef BACKGROUND_MUSIC_H_
#define BACKGROUND_MUSIC_H_

#include <string>
#include <unordered_map>

// BGM�N���X
class BackgroundMusic {
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
    // BGM�̍Đ�
    static void play();
    // BGM�̒�~
    static void stop();
private:
    // �o�C���h����BGM
    static int bgm_;
    // BGM�n���h��
    static std::unordered_map<int, int> bgm_map_;
};

#endif
