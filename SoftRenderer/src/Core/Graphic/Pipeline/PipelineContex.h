#pragma once
#include "Core/Graphic/Renderer/DeviceAPI.h"
#include <vector>

class IRenderer;
class PipelineContex {
 public:
	void Clear();

 public:
	IDeviceAPI * _pDeviceAPI;
	std::vector<Vertex> _vertexes;
	std::vector<int> _indexes;
	std::vector<Fragment> _fragments;
};
