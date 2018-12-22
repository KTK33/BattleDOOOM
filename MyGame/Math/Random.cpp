#include "Random.h"

// ����������
std::mt19937 Random::mt_;
// �����̃V�[�h
unsigned int Random::seed_{ std::mt19937::default_seed };

// ����������̏�����
void Random::randomize() {
    std::random_device rd;
    randomize(rd());
}

// ����������̏�����
void Random::randomize(unsigned int seed) {
    seed_ = seed;
    mt_ = std::mt19937(seed_);
}

// int�^�̗��������߂�
int Random::rand(int l, int h) {
    std::uniform_int_distribution<int> dist(l, h);
    return dist(mt_);
}

// float�^�̗��������߂�
float Random::rand(float l, float h) {
    std::uniform_real_distribution<float> dist(l, h);
    return dist(mt_);
}

// �����̃V�[�h���擾
unsigned int Random::seed() {
    return seed_;
}

// end of file
