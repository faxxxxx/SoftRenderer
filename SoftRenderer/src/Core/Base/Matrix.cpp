#include "Matrix.h"

Vector4f Matrix4x4f::MultiplyVector4(const Vector4f & inV) const {
	Vector4f ret;
	MultiplyVector4(inV, ret);
	return ret;
}