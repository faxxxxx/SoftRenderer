#pragma once
#include "Core/Base/Matrix.h"

class Camera {
 public:
	enum Projection {
		Orthographic = 0,
		Perspective
	};

	void SetProjectionType(Projection projType);
	void SetClippingPlanes(float nearVal, float farVal);
	void SetFieldOfView(float fov);
    Matrix4x4f GetCameraMatix();
	Matrix4x4f GetProjectMatrix();
	void SetViewPort(int w, int h);

    void SetPosition(const Vector3f &pos);
    void SetLookAt(const Vector3f &dir);
    
 private:
	Projection _projectType = Orthographic;
	float _clippingPlanesNear = 0.0f;
	float _clippingPlanesFar = 0.0f;
	float _fov = 1.0f;
	int _viewPortWidth = 0;
	int _viewPortHeight = 0;
    Vector3f _pos;
    Vector3f _lookAt;
    
	const static float FovMax;
	const static float FovMin;
};
