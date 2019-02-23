#include"MatrixRotation.h"
#include "../../Input/GamePad.h"
#include <cmath>

constexpr float maxup{ 40.0f };
constexpr float maxangle{ 360.0f };
constexpr float eventangle{ 90.0f };

MatrixRotation::MatrixRotation() {}

void MatrixRotation::initialize(Matrix& rotation) {
	verticalangle_ = Matrix::Angle(rotation).x;
	horizontalangle_ = -Matrix::Angle(rotation).y;
}

Matrix MatrixRotation::update() {
	Matrix result{ Matrix::Identity };
	is_eventReset = false;
	move(true);
	if (is_normalReset) {
		amount = MathHelper::Clamp(amount + 0.04f, 0.0f, 1.0f);
		verticalangle_ = MathHelper::Lerp(start_x, 0.0f, MathHelper::Smoothstep(0.0f, 1.0f, amount));
		if (amount >= 1.0f) {
			is_normalReset = false;
		}
	}
	result *= Matrix::CreateFromAxisAngle(result.Up(), horizontalangle_);
	result *= Matrix::CreateFromAxisAngle(result.Right(), verticalangle_);
	return result;
}
Matrix MatrixRotation::eventUpdate() {
	Matrix result{ Matrix::Identity };
	is_normalReset = false;

	eRot = Matrix::Angle(endInitializeRotation).y;
	if (eRot < 0.0f) eRot += 360.0f;
	if (horizontalangle_ > eRot + eventangle) horizontalangle_ -= 360.0f;
	else if(horizontalangle_ < eRot - eventangle) horizontalangle_ += 360.0f;

	move(false);

	if (is_eventReset) {
		amount = MathHelper::Clamp(amount + 0.04f, 0.0f, 1.0f);
		if (eRot - start_y > 180.0f) {
			eRot -= 360.0f;
		}
		if (start_y - eRot > 180.0f) {
			start_y -= 360.0f;
		}
		horizontalangle_ = MathHelper::Lerp(start_y, eRot, MathHelper::Smoothstep(0.0f, 1.0f, amount));
		verticalangle_ = MathHelper::Lerp(start_x, Matrix::Angle(endInitializeRotation).x, MathHelper::Smoothstep(0.0f, 1.0f, amount));
		if (amount > 1.0f) {
			is_eventReset = false;
		}
	}
	result *= Matrix::CreateFromAxisAngle(result.Up(), horizontalangle_);
	result *= Matrix::CreateFromAxisAngle(result.Right(), verticalangle_);
	return result;
}

Matrix MatrixRotation::resetOnlyUpdate()
{

	Matrix result{ Matrix::Identity };
	if (is_eventReset) {
		amount = MathHelper::Clamp(amount + 0.04f, 0.0f, 1.0f);
		if (eRot - start_y > 180.0f) {
			eRot -= 360.0f;
		}
		if (start_y - eRot > 180.0f) {
			start_y -= 360.0f;
		}
		horizontalangle_ = MathHelper::Lerp(start_y, eRot, MathHelper::Smoothstep(0.0f, 1.0f, amount));
		verticalangle_ = MathHelper::Lerp(start_x, Matrix::Angle(endInitializeRotation).x, MathHelper::Smoothstep(0.0f, 1.0f, amount));
		if (amount > 1.0f) {
			is_eventReset = false;
		}
	}
	result *= Matrix::CreateFromAxisAngle(result.Up(), horizontalangle_);
	result *= Matrix::CreateFromAxisAngle(result.Right(), verticalangle_);
	return result;
}

void MatrixRotation::move(const bool& limit)
{
	Vector2 rotate = GamePad::GetInstance().RightStick();

	if (rotate.Length() > 0.2f) {
		rotate *= (6.0f * sens_);
		verticalangle_ = MathHelper::Clamp(verticalangle_ + rotate.y, -maxup, maxup);
		horizontalangle_ = (limit) ? fmodf(horizontalangle_ + rotate.x, maxangle) : MathHelper::Clamp(horizontalangle_ + rotate.x, eRot - eventangle, eRot + eventangle);
		is_normalReset = false;
		is_eventReset = false;
	}
}

void MatrixRotation::SetEventRotation(const Matrix& mat) {
	endInitializeRotation = mat;
	eRot = Matrix::Angle(endInitializeRotation).y;
	if (eRot < 0.0f) eRot += 360.0f;
	if (horizontalangle_ < 0.0f) horizontalangle_ += 360.0f;
}

void MatrixRotation::NormalReset(const Matrix& mat) {
	start_x = verticalangle_;
	amount = 0.0f;
	is_normalReset = true;
}
void MatrixRotation::EventReset(const Matrix& start) {
	start_x = verticalangle_;
	start_y = horizontalangle_;
	if (start_y < 0.0f) start_y += 360.0f;
	amount = 0.0f;
	is_eventReset = true;
}

float & MatrixRotation::sens()
{
	return sens_;
}
