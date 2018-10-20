#include "PipelineContex.h"

void PipelineContex::Init(IDeviceAPI *pDeviceApi) {
	_pDeviceAPI = pDeviceApi;
	auto w = pDeviceApi->PixelWidth();
	auto h = pDeviceApi->PixelHeight();
	_colorBuffer = new Color[w * h];
	_depthBuffer = new float[w * h];
}

void PipelineContex::Clear() {
	_vertexes.clear();
	_indexes.clear();
	_fragments.clear();

	auto w = _pDeviceAPI->PixelWidth();
	auto h = _pDeviceAPI->PixelHeight();
	memset(_colorBuffer, 0, sizeof(Color) * w * h);
	for (int i = 0; i < w * h; i++)
		_depthBuffer[i] = 1.0f;
}