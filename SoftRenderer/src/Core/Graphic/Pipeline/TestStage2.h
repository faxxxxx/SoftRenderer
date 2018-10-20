#pragma once
#include "PipelineStage.h"
#include "Core/Graphic/Camera/Camera.h"

#include <vector>
#include "Rasterizer.h"

class TestStage2 : public PipelineStage {
 public:
	Camera _cam;

	std::vector<Vertex> _verts;
	std::vector<unsigned int> _indexes;

	TestStage2() {
		Vertex v1;
		v1.color = Color(1.0f, 0.0, 0, 1.0f);
		v1.pos = Vector3f(0.75f, 300, 0.0f);
		_verts.push_back(v1);
	}

	virtual void Init(PipelineContex *ctx) override {
		_cam.SetClippingPlanes(100, 1000);
		_cam.SetProjectionType(Camera::Perspective);
		_cam.SetFieldOfView(45);
		_cam.SetViewPort(ctx->_pDeviceAPI->PixelWidth(), ctx->_pDeviceAPI->PixelHeight());
	}

	virtual bool Execute(PipelineContex *ctx) override {
		//for (int i = 0; i < 1000; i++)
		//{
		//	int x = rand() % ctx->_pDeviceAPI->PixelWidth();
		//	int y = rand() % ctx->_pDeviceAPI->PixelHeight();
		//	ctx->_pDeviceAPI->DrawPixel(x, y, Color(1.0f, 0, 0, 1));
		//}

		int w = ctx->_pDeviceAPI->PixelWidth();
		int h = ctx->_pDeviceAPI->PixelHeight();

		//std::vector<Vector2f> points{
		//	Vector2f(0.3f * w, 0.5f * h),
		//	Vector2f(0.25f * w, 0.66f * h),
		//	Vector2f(0.5f * w, 0.75f * h),
		//};

		////ctx->_pDeviceAPI->DrawLine(Vector2f(0.5f * w, 0.5f * h), Vector2f(w, 0.5f * h), Color(1.0f, 0, 0, 1));
		//ctx->_pDeviceAPI->DrawLine(points[0], points[1], Color(1.0f, 0, 0, 1));
		//ctx->_pDeviceAPI->DrawLine(points[1], points[2], Color(1.0f, 0, 0, 1));
		//ctx->_pDeviceAPI->DrawLine(points[2], points[0], Color(1.0f, 0, 0, 1));

		Vertex v1;
		v1.color = Color(1.0f, 0.0, 0, 1.0f);
		v1.pos = Vector3f(0.75f * w, 300, 0.0f);

		Vertex v2;
		v2.color = Color(0, 1, 0, 1.0f);
		v2.pos = Vector3f(0.5f * w, 100, 0.0f);

		Vertex v3;
		v3.color = Color(0, 0, 1.0f, 1.0f);
		v3.pos = Vector3f(0.9f * w, 200, 0.0f);

		std::vector<Fragment> pts;
		pts.reserve(w*h);
		Rasterizer::Rasterize(v1, v2, v3, pts);
		for (auto &pt : pts) {
			ctx->_pDeviceAPI->DrawPixel(Vector2f(pt.pos.x, pt.pos.y), pt.color);
		}

		return true;
	}

 private:
};