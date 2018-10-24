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
    auto right = Vector3f(0.0f, 1.0f, 0.0f).Cross(_lookAt);
    right.Normalize();
    auto up = _lookAt.Cross(right);
    up.Normalize();
    
    ret[0] = right.x;
    ret[1] = right.y;
    ret[2] = right.z;
    ret[4] = up.x;
    ret[5] = up.y;
    ret[6] = up.z;
    ret[8] = _lookAt.x;
    ret[9] = _lookAt.y;
    ret[10] = _lookAt.z;
    
    ret[3] = -right.Dot(_pos);
    ret[7] = -up.Dot(_pos);
    ret[11] = -_lookAt.Dot(_pos);
    
    ret[12] = ret[13] = ret[14] = 0.0f;
    return ret;
}


