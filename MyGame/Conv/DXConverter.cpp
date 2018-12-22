#include "DXConverter.h"

VECTOR DXConverter::ToVECTOR(const Vector3 & v) const
{
	return VGet(v.x, v.y, v.z);
}

Vector3 DXConverter::ToVector3(const VECTOR & v) const
{
	return Vector3(v.x, v.y, v.z);
}

int DXConverter::ToColor(const Vector3 & v) const
{
	return (int)GetColor((int)v.x, (int)v.y, (int)v.z);
}

MATRIX DXConverter::ToMATRIX(const Matrix & m) const
{
	MATRIX result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m.m[i][j];
		}
	}
	return result;
}

MATRIX_D DXConverter::ToMATRIX_D(const Matrix & m) const
{
	MATRIX_D result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m.m[i][j];
		}
	}
	return result;
}

Matrix DXConverter::ToMatrix(const MATRIX & m) const
{
	Matrix result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m.m[i][j];
		}
	}
	return result;
}
