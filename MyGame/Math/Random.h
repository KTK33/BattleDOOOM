#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

// 乱数クラス
class Random {
public:
    // 乱数生成器の初期化
    static void randomize();
    // 乱数生成器の初期化
    static void randomize(unsigned int seed);
    // int型の乱数を求める
    static int rand(int l, int h);
    // float型の乱数を求める
    static float rand(float l, float h);
    // 乱数のシードを取得
    static unsigned int seed();
private:
    // 乱数生成器
    static std::mt19937 mt_;
    // 乱数のシード
    static unsigned int seed_;
};

#endif

// end of file
