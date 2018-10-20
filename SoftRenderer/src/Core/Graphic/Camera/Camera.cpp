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

Matrix4x4f Camera::GetProjectMatrix()
{
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

void Camera::SetViewPort(int w, int h)
{
	_viewPortWidth = w;
	_viewPortHeight = h;
}
