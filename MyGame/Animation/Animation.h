#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <array>
#include "../Mesh/SkeletalMesh.h"

class Animation
{
public:
	using Matrices = std::array<Matrix, 256>;
public:
	//コンストラクタ
	Animation(int model, int motion);
	//更新
	void update(float delta_time);
	//モーションの変更
	void change_motion(int motion);
	//現在再生中のモーション
	int motion() const;
	//変換行列の取得
	const Matrices& local_matrices() const;
	//ボーン数を返す
	int bone_const() const;
	//終了時間を返す
	float end_time() const;
private:
	//補間フレーム数
	const float LerpTime{ 10.0f };
	//アニメーション番号
	int model_{ 0 };
	//再生中のモーション番号
	int motion_{ 0 };
	//再生中のアニメーションタイマ
	float motion_timer_{ 0.0f };
	//前回再生したモーション番号
	int prev_motion_{ 0 };
	//前回再生した最終アニメーションタイマ
	float prev_motion_timer_{ 0.0f };
	//補間アニメーションタイマ
	float lerp_timer_{ 0.0f };
	//アニメーション変換行列
	Matrices local_matrices_;
};


#endif // !ANIMATION_H_

