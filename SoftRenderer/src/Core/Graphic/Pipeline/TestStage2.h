#pragma once
#include "PipelineStage.h"
#include "Core/Graphic/Camera/Camera.h"

#include <vector>
#include "Rasterizer.h"

#include "png.h"

class TestStage2 : public PipelineStage {
 public:
	Camera _cam;
	float _angle = 0.0f;
	std::vector<Vertex> _verts;
	std::vector<unsigned int> _indexes;

	TestStage2() {
		//front
		AddVertex(Vector3f(-50.0f, 50.0f, -50.0f), Color(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f));
		AddVertex(Vector3f(50.0f, 50.0f, -50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f));
		AddVertex(Vector3f(50.0f, -50.0f, -50.0f), Color(1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
		AddVertex(Vector3f(-50.0f, -50.0f, -50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f));

		//back
		AddVertex(Vector3f(-50.0f, 50.0f, 50.0f), Color(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f));
		AddVertex(Vector3f(50.0f, 50.0f, 50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f));
		AddVertex(Vector3f(50.0f, -50.0f, 50.0f), Color(1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
		AddVertex(Vector3f(-50.0f, -50.0f, 50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f));

		//left
		AddVertex(Vector3f(-50.0f, 50.0f, 50.0f), Color(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f));
		AddVertex(Vector3f(-50.0f, 50.0f, -50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f));
		AddVertex(Vector3f(-50.0f, -50.0f, -50.0f), Color(1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
		AddVertex(Vector3f(-50.0f, -50.0f, 50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f));

		//right
		AddVertex(Vector3f(50.0f, 50.0f, 50.0f), Color(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f));
		AddVertex(Vector3f(50.0f, 50.0f, -50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f));
		AddVertex(Vector3f(50.0f, -50.0f, -50.0f), Color(1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
		AddVertex(Vector3f(50.0f, -50.0f, 50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f));

		//top
		AddVertex(Vector3f(-50.0f, 50.0f, 50.0f), Color(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f));
		AddVertex(Vector3f(50.0f, 50.0f, 50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f));
		AddVertex(Vector3f(50.0f, 50.0f, -50.0f), Color(1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
		AddVertex(Vector3f(-50.0f, 50.0f, -50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f));

		//bottom
		AddVertex(Vector3f(-50.0f, -50.0f, 50.0f), Color(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f));
		AddVertex(Vector3f(50.0f, -50.0f, 50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f));
		AddVertex(Vector3f(50.0f, -50.0f, -50.0f), Color(1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
		AddVertex(Vector3f(-50.0f, -50.0f, -50.0f), Color(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f));

		_indexes.assign({
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20
		});
	}

	void AddVertex(const Vector3f& pos, const Color& c, const Vector2f &uv) {
		_verts.push_back(Vertex(pos, c, uv));
	}

	virtual void Init(PipelineContex *ctx) override {
		_cam.SetClippingPlanes(100, 1000);
		_cam.SetProjectionType(Camera::Perspective);
		_cam.SetFieldOfView(60);
		_cam.SetViewPort(ctx->_pDeviceAPI->PixelWidth(), ctx->_pDeviceAPI->PixelHeight());
		_cam.SetPosition(Vector3f(0.0f, 200.0f, -200.0f));
		_cam.SetLookAt(Vector3f(0.0f, -10.0f, 10.0f));
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
//        ctx->SetWireFrameMode(true);

		//std::vector<Vector2f> points{
		//	Vector2f(0.3f * w, 0.5f * h),
		//	Vector2f(0.25f * w, 0.66f * h),
		//	Vector2f(0.5f * w, 0.75f * h),
		//};

		////ctx->_pDeviceAPI->DrawLine(Vector2f(0.5f * w, 0.5f * h), Vector2f(w, 0.5f * h), Color(1.0f, 0, 0, 1));
		//ctx->_pDeviceAPI->DrawLine(points[0], points[1], Color(1.0f, 0, 0, 1));
		//ctx->_pDeviceAPI->DrawLine(points[1], points[2], Color(1.0f, 0, 0, 1));
		//ctx->_pDeviceAPI->DrawLine(points[2], points[0], Color(1.0f, 0, 0, 1));

//        Vertex v1;
//        v1.color = Color(1.0f, 0.0, 0, 1.0f);
//        v1.pos = Vector3f(0.75f * w, 300, 0.0f);
//
//        Vertex v2;
//        v2.color = Color(0, 1, 0, 1.0f);
//        v2.pos = Vector3f(0.5f * w, 100, 0.0f);
//
//        Vertex v3;
//        v3.color = Color(0, 0, 1.0f, 1.0f);
//        v3.pos = Vector3f(0.9f * w, 200, 0.0f);
//
//        std::vector<Fragment> pts;
//        pts.reserve(w*h);
//        Rasterizer::Rasterize(v1, v2, v3, pts);
//        for (auto &pt : pts) {
//            ctx->_pDeviceAPI->DrawPixel(Vector2f(pt.pos.x, pt.pos.y), pt.color);
//        }

		auto mat = _cam.GetProjectMatrix();
		auto camMat = _cam.GetCameraMatix();

		Matrix4x4f rotateMat;
		_angle += 0.4f;
		if (_angle > 360.0f) {
			_angle = 0.0f;
		}
		rotateMat.RotateAxixY(_angle);

		mat = mat.MultiplyMatrix4x4(camMat);
		mat = mat.MultiplyMatrix4x4(rotateMat);
		for(auto &v : _verts) {
			ctx->_vertexes.emplace_back(ConvertToProjectionSpace(v.pos, mat), v.color, v.uv);
		}
		ctx->_indexes.insert(ctx->_indexes.end(), _indexes.begin(), _indexes.end());
		return true;
	}

 private:

	Vector3f ConvertToProjectionSpace(const Vector3f &p, const Matrix4x4f &mat) {
		auto result = mat.MultiplyVector4(Vector4f(p));
		assert(!FloatIsZero(result.w));
		return Vector3f(result.x/result.w, result.y/result.w, result.z/result.w);
	}
};
