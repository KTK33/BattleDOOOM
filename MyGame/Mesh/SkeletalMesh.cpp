#include "SkeletalMesh.h"
#include <DxLib.h>

// バインド中のモデル
int SkeletalMesh::model_{ -1 };
// ボーンのローカル変換行列
Matrix SkeletalMesh::local_matrices_[SkeletalMesh::BoneMax];
// ボーンのワールド変換行列
Matrix SkeletalMesh::world_matrices_[SkeletalMesh::BoneMax];
// モデルアセット
ModelAsset SkeletalMesh::asset_;

// 初期化
void SkeletalMesh::initialize() {
    finalize();
}

// 終了処理
void SkeletalMesh::finalize() {
    asset_.clear();
    model_ = -1;
}

// 読み込み
bool SkeletalMesh::load(int id, const std::string & file_name) {
    return asset_.load(id, file_name);
}

// 削除
void SkeletalMesh::erase(int id) {
    model_ = (model_ == asset_[id]) ? -1 : model_;
    asset_.erase(id);
}

// メッシュのバインド
void SkeletalMesh::bind(int id) {
    model_ = asset_[id];
}

// 描画
void SkeletalMesh::draw() {
    for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
        MV1ResetFrameUserLocalMatrix(model_, i);
        MV1SetFrameUserLocalWorldMatrix(model_, i, world_matrices_[i]);
    }
    MV1DrawModel(model_);
}

// ローカル変換行列を計算
void SkeletalMesh::bind_animation(int motion, float time) {
    const auto index = MV1AttachAnim(model_, motion);
    MV1SetAttachAnimTime(model_, index, time);
    for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
        MV1ResetFrameUserLocalMatrix(model_, i);
        local_matrices_[i] = MV1GetFrameLocalMatrix(model_, i);
    }
    MV1DetachAnim(model_, index);
}

// ローカル変換行列を計算
void SkeletalMesh::bind_animation(int prev_motion, float prev_time, int motion, float time, float amount) {
    const auto prev_index = MV1AttachAnim(model_, prev_motion);
    const auto now_index = MV1AttachAnim(model_, motion);
    MV1SetAttachAnimBlendRate(model_, prev_index, 1.0f - amount);
    MV1SetAttachAnimBlendRate(model_, now_index, amount);
    MV1SetAttachAnimTime(model_, prev_index, prev_time);
    MV1SetAttachAnimTime(model_, now_index, time);
    for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
        MV1ResetFrameUserLocalMatrix(model_, i);
        local_matrices_[i] = MV1GetFrameLocalMatrix(model_, i);
    }
    MV1DetachAnim(model_, prev_index);
    MV1DetachAnim(model_, now_index);
}

// ワールド変換行列を計算する
void SkeletalMesh::transform(const Matrix & world) {
    // ローカル変換行列を設定
    for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
        MV1SetFrameUserLocalMatrix(model_, i, local_matrices_[i]);
    }
    // ワールド変換行列を設定
    MV1SetMatrix(model_, world);
    // ワールド変換行列を取得
    for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
        world_matrices_[i] = MV1GetFrameLocalWorldMatrix(model_, i);
    }
}

// ローカル変換行列の取得
void SkeletalMesh::get_local_matrices(Matrix local_matrices[]) {
    for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
        local_matrices[i] = local_matrices_[i];
    }
}

// ワールド変換行列の設定
void SkeletalMesh::set_local_matrices(const Matrix local_matrices[]) {
    for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
        world_matrices_[i] = local_matrices[i];
    }
}

// ワールド変換行列の取得
void SkeletalMesh::get_world_matrices(Matrix world_matrices[]) {
    for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
        world_matrices[i] = world_matrices_[i];
    }
}

// ワールド変換行列の設定
void SkeletalMesh::set_world_matrices(const Matrix world_matrices[]) {
    for (int i = 0; i < MV1GetFrameNum(model_); ++i) {
        world_matrices_[i] = world_matrices[i];
    }
}

// ボーン数の取得
int SkeletalMesh::bone_count() {
    return MV1GetFrameNum(model_);
}

// 終了時間を返す
float SkeletalMesh::end_time(int motion) {
    return MV1GetAnimTotalTime(model_, motion);
}

void SkeletalMesh::Transparence(float alpha)
{
	MV1SetOpacityRate(model_, alpha);
}
