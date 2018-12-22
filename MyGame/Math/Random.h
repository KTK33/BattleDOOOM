#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

// �����N���X
class Random {
public:
    // ����������̏�����
    static void randomize();
    // ����������̏�����
    static void randomize(unsigned int seed);
    // int�^�̗��������߂�
    static int rand(int l, int h);
    // float�^�̗��������߂�
    static float rand(float l, float h);
    // �����̃V�[�h���擾
    static unsigned int seed();
private:
    // ����������
    static std::mt19937 mt_;
    // �����̃V�[�h
    static unsigned int seed_;
};

#endif

// end of file
