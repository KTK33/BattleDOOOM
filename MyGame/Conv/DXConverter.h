#pragma once
#include "DxLib.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"
#include "../Math/Matrix.h"

class DXConverter
{
private:
	DXConverter() = default;
	~DXConverter() = default;

public:
	static DXConverter &GetInstance()
	{
		static DXConverter d;
		return d;
	}

	// Vector3¨VECTOR‚É•ÏŠ·‚µ‚Ä•Ô‚·
	VECTOR ToVECTOR(const Vector3& v) const;
	// VECTOR¨Vector3‚É•ÏŠ·‚µ‚Ä•Ô‚·
	Vector3 ToVector3(const VECTOR& v) const;

	// Vector3¨Color‚É•ÏŠ·‚µ‚Ä•Ô‚·
	int ToColor(const Vector3& v) const;

	// Matrix¨MATRIX‚É•ÏŠ·‚µ‚Ä•Ô‚·
	MATRIX ToMATRIX(const Matrix& m) const;
	MATRIX_D ToMATRIX_D(const Matrix& m) const;
	// MATRIX¨Matrix‚É•ÏŠ·‚µ‚Ä•Ô‚·
	Matrix ToMatrix(const MATRIX& m) const;
};