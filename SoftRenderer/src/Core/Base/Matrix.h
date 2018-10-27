#pragma once
#include "BaseType.h"
#include <memory.h>
#include <math.h>
#include <fstream>

class Matrix4x4f {
 public:
	float _data[16];

	// 0  1  2  3
	// 4  5  6  7
	// 8  9  10 11
	// 12 13 14 15
	Matrix4x4f() {
		LoadIdentity();
	}

	float& Get(int row, int column) {
		return _data[row + (column * 4)];
	}
	const float& Get(int row, int column)const {
		return _data[row + (column * 4)];
	}
	float operator [] (int index) const {
		return _data[index];
	}
	float& operator [] (int index) {
		return _data[index];
	}
	void LoadIdentity() {
		memset(_data, 0, sizeof(_data));
		_data[0] = _data[5] = _data[10] = _data[15] = 1.0f;
	}

	void Transpose() {
		std::swap(_data[1], _data[4]);
		std::swap(_data[2], _data[8]);
		std::swap(_data[3], _data[12]);
		std::swap(_data[6], _data[9]);
		std::swap(_data[7], _data[13]);
		std::swap(_data[11], _data[14]);
	}

	void Inverse() {

	}

	void RotateAxixY(float angle) {
		Get(0, 0) = cos(Angle2Rad(angle));
		Get(0, 2) = -sin(Angle2Rad(angle));
		Get(2, 0) = -Get(0, 2);
		Get(2, 2) = Get(0, 0);
	}

	Vector4f MultiplyVector4(const Vector4f& inV) const;
	void MultiplyVector4(const Vector4f& inV, Vector4f& output) const;
	Matrix4x4f MultiplyMatrix4x4(const Matrix4x4f& mat) const;
};

inline void Matrix4x4f::MultiplyVector4(const Vector4f & inV, Vector4f & output) const {
	output.x = Get(0, 0) * inV.x + Get(1, 0) * inV.y + Get(2, 0) * inV.z + Get(3, 0) * inV.w;
	output.y = Get(0, 1) * inV.x + Get(1, 1) * inV.y + Get(2, 1) * inV.z + Get(3, 1) * inV.w;
	output.z = Get(0, 2) * inV.x + Get(1, 2) * inV.y + Get(2, 2) * inV.z + Get(3, 2) * inV.w;
	output.w = Get(0, 3) * inV.x + Get(1, 3) * inV.y + Get(2, 3) * inV.z + Get(3, 3) * inV.w;
}

inline Vector4f Matrix4x4f::MultiplyVector4(const Vector4f& inV) const {
	Vector4f ret;
	MultiplyVector4(inV, ret);
	return ret;
}

inline Matrix4x4f Matrix4x4f::MultiplyMatrix4x4(const Matrix4x4f& mat) const {
	// 0  1  2  3
	// 4  5  6  7
	// 8  9  10 11
	// 12 13 14 15
	auto& data2 = mat._data;
	Matrix4x4f ret;
	ret[0] = _data[0] * data2[0] + _data[1] * data2[4] + _data[2] * data2[8] + _data[3] * data2[12];
	ret[1] = _data[0] * data2[1] + _data[1] * data2[5] + _data[2] * data2[9] + _data[3] * data2[13];
	ret[2] = _data[0] * data2[2] + _data[1] * data2[6] + _data[2] * data2[10] + _data[3] * data2[14];
	ret[3] = _data[0] * data2[3] + _data[1] * data2[7] + _data[2] * data2[11] + _data[3] * data2[15];

	ret[4] = _data[4] * data2[0] + _data[5] * data2[4] + _data[6] * data2[8] + _data[7] * data2[12];
	ret[5] = _data[4] * data2[1] + _data[5] * data2[5] + _data[6] * data2[9] + _data[7] * data2[13];
	ret[6] = _data[4] * data2[2] + _data[5] * data2[6] + _data[6] * data2[10] + _data[7] * data2[14];
	ret[7] = _data[4] * data2[3] + _data[5] * data2[7] + _data[6] * data2[11] + _data[7] * data2[15];

	ret[8] = _data[8] * data2[0] + _data[9] * data2[4] + _data[10] * data2[8] + _data[11] * data2[12];
	ret[9] = _data[8] * data2[1] + _data[9] * data2[5] + _data[10] * data2[9] + _data[11] * data2[13];
	ret[10] = _data[8] * data2[2] + _data[9] * data2[6] + _data[10] * data2[10] + _data[11] * data2[14];
	ret[11] = _data[8] * data2[3] + _data[9] * data2[7] + _data[10] * data2[11] + _data[11] * data2[15];

	ret[12] = _data[12] * data2[0] + _data[13] * data2[4] + _data[14] * data2[8] + _data[15] * data2[12];
	ret[13] = _data[12] * data2[1] + _data[13] * data2[5] + _data[14] * data2[9] + _data[15] * data2[13];
	ret[14] = _data[12] * data2[2] + _data[13] * data2[6] + _data[14] * data2[10] + _data[15] * data2[14];
	ret[15] = _data[12] * data2[3] + _data[13] * data2[7] + _data[14] * data2[11] + _data[15] * data2[15];
	return ret;
}
