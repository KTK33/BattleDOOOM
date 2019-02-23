#pragma once

#include "../../Math/Vector3.h"

class TPSCamera
{
private:
	// �J�����̎��_���W�N���X
	struct CPosition
	{
		Vector3 position_;
		Vector3 Get() const { return position_; }
		void Set(const Vector3& position) { position_ = position; }

	};

	// �J�����̒����_���W�N���X
	class CTarget
	{
	private:
		Vector3 target_;
	public:
		Vector3 Get() const { return target_; }
		void Set(const Vector3& target) { target_ = target; }
	};

	// �J�����̏�����N���X
	struct CUp
	{
	private:
		Vector3 up_;
	public:
		Vector3 Get() const { return up_; }
		void Set(const Vector3& up) { up_ = up; }
	};

private:
	TPSCamera() = default;
	~TPSCamera() = default;

public:
	static TPSCamera& GetInstance()
	{
		static TPSCamera c;
		return c;
	}

	void Initialize();
	// �X�V
	void Update();
	// �J�����̕`�拗����ݒ肷��i��O�����A�������j
	void SetRange(float Near, float Far);
	// �J�����̉�]�p�x��ݒ肷��i������]�p�x�A������]�p�x�A�P���]�p�x�j
	void SetRotation(Vector3 rotate);
	// �w�肵�����W���J�����̎��E�ɓ����Ă��邩�ۂ�
	bool IsCheckView(Vector3 position);
	// �w�肵���{�b�N�X�̈悪�J�����̎��E�ɓ����Ă��邩
	bool IsCheckView(Vector3 min, Vector3 max);
	// �J�����̎���p��ݒ肷��i�O�`�R�U�O�x�j
	void SetViewAngle(float degree);

public:
	CPosition	Position;
	CTarget		Target;
	CUp			Up;
	float near_, far_, degree_;
};