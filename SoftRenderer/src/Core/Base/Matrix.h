#pragma once
#include "BaseType.h"
#include <memory.h>

class Matrix4x4f {
 public:
	float _data[16];

	Matrix4x4f() {
		memset(_data, 0, sizeof(_data));
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

	Vector4f MultiplyVector4(const Vector4f& inV) const;
	void MultiplyVector4(const Vector4f& inV, Vector4f& output) const;
};

inline void Matrix4x4f::MultiplyVector4(const Vector4f & inV, Vector4f & output) const {
	output.x = _data[0] * inV.x + _data[1] * inV.y + _data[2] * inV.z + _data[3] * inV.w;

	output.y = _data[4] * inV.x + _data[5] * inV.y + _data[6] * inV.z + _data[7] * inV.w;
	output.z = _data[8] * inV.x + _data[9] * inV.y + _data[10] * inV.z + _data[11] * inV.w;
	output.w = _data[12] * inV.x + _data[13] * inV.y + _data[14] * inV.z + _data[15] * inV.w;
}
