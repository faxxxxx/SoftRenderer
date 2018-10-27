#include "Camera.h"
#include <math.h>

const float Camera::FovMax = 179.0f;
const float Camera::FovMin = 1.0f;

void Camera::SetProjectionType(Projection projType) {
	_projectType = projType;
}

void Camera::SetClippingPlanes(float nearVal, float farVal) {
	_clippingPlanesNear = nearVal;
	_clippingPlanesFar = farVal;
}

void Camera::SetFieldOfView(float fov) {
	_fov = fov;
	if (_fov < FovMin)
		_fov = FovMin;
	if (_fov > FovMax)
		_fov = FovMax;
}

Matrix4x4f Camera::GetProjectMatrix() {
	Matrix4x4f ret;
	float rr = (float)_viewPortHeight / _viewPortWidth; // 1/r
	float a = _fov / 2.0f * PI / 180.0f;
	float v = 1 / tan(a); // cot(a/2)
	float f = _clippingPlanesFar;
	float n = _clippingPlanesNear;
	float d = f - n;

	ret[0] = rr * v; // 1/r * cot(a/2)
	ret[5] = v;// cot(a/2)
	ret[10] = f / d;
	ret[11] = -f * n / d;
	ret[14] = 1;
	return ret;
}

void Camera::SetViewPort(int w, int h) {
	_viewPortWidth = w;
	_viewPortHeight = h;
}

void Camera::SetPosition(const Vector3f &pos) {
	_pos = pos;
}

void Camera::SetLookAt(const Vector3f &dir) {
	_lookAt = dir;
	_lookAt.Normalize();
}

Matrix4x4f Camera::GetCameraMatix() {
	Matrix4x4f ret;
	auto right = _lookAt.Cross(Vector3f::Up);
	right.Normalize();
	auto up = right.Cross(_lookAt);
	up.Normalize();

	ret.Get(0, 0) = right.x;
	ret.Get(1, 0) = right.y;
	ret.Get(2, 0) = right.z;
	ret.Get(0, 1) = up.x;
	ret.Get(1, 1) = up.y;
	ret.Get(2, 1) = up.z;
	ret.Get(0, 2) = _lookAt.x;
	ret.Get(1, 2) = _lookAt.y;
	ret.Get(2, 2) = _lookAt.z;

	ret.Get(3, 0) = -right.Dot(_pos);
	ret.Get(3, 1) = -up.Dot(_pos);
	ret.Get(3, 2) = -_lookAt.Dot(_pos);
	ret.Get(3, 3) = 1.0f;

	return ret;
}


