#ifndef ANIMATION_MESH_H_
#define ANIMATION_MESH_H_

#include "../Mesh/SkeletalMesh.h"
#include "Animation.h"
//アニメーション付きメッシュクラス
class AnimatedMesh
{
public:
	//コンストラクタ
	AnimatedMesh(int mesh, int motion = 0);
	//更新
	void update(float deltaTime);
	//描画
	void draw() const;
	//モーションの変更
	void change_motion(int motion);
	//スケルトンの変換行列を計算する
	void transform(const Matrix& world);
	//変換行列を取得
	const Matrix& bone_matrix(int no) const;
	//モーションの終了時間を取得
	float motion_end_time() const;

private:
	//スケルトン変換行列
	using BoneMatrices = std::array<Matrix, 256>;
	//メッシュ
	int mesh_;
	//アニメーション
	Animation animation_;
	//スケルトン変換行列
	BoneMatrices world_matrices_;
};
#endif // !ANIMATION_MESH_H_
