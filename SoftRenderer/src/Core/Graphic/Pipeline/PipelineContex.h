#pragma once
#include "Core/Graphic/Renderer/DeviceAPI.h"
#include <vector>

class IRenderer;
class PipelineContex {
 public:
	void Init(IDeviceAPI *pDeviceApi);
	void Clear();
    void SetWireFrameMode(bool b)
    {
        _isWireFrameMode = b;
    }
    bool IsWireFrameMode() { return _isWireFrameMode; }
    
 public:
	IDeviceAPI * _pDeviceAPI;
	std::vector<Vertex> _vertexes;
	std::vector<unsigned int> _indexes;
	std::vector<Fragment> _fragments;

    bool _isWireFrameMode = false;
    
	Color *_colorBuffer = nullptr;
	float *_depthBuffer = nullptr;
};
