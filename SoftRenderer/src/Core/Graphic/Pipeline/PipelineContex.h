#pragma once
#include "Core/Graphic/Renderer/DeviceAPI.h"
#include <vector>

class IRenderer;
class PipelineContex {
 public:
	void Init(IDeviceAPI *pDeviceApi);
	void Clear();

 public:
	IDeviceAPI * _pDeviceAPI;
	std::vector<Vertex> _vertexes;
	std::vector<unsigned int> _indexes;
	std::vector<Fragment> _fragments;

	Color *_colorBuffer = nullptr;
	float *_depthBuffer = nullptr;
};
