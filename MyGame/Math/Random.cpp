#include "Random.h"

// 乱数生成器
std::mt19937 Random::mt_;
// 乱数のシード
unsigned int Random::seed_{ std::mt19937::default_seed };

// 乱数生成器の初期化
void Random::randomize() {
    std::random_device rd;
    randomize(rd());
}

// 乱数生成器の初期化
void Random::randomize(unsigned int seed) {
    seed_ = seed;
    mt_ = std::mt19937(seed_);
}

// int型の乱数を求める
int Random::rand(int l, int h) {
    std::uniform_int_distribution<int> dist(l, h);
    return dist(mt_);
}

// float型の乱数を求める
float Random::rand(float l, float h) {
    std::uniform_real_distribution<float> dist(l, h);
    return dist(mt_);
}

// 乱数のシードを取得
unsigned int Random::seed() {
    return seed_;
}

// end of file
