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

bool PipelineContex::CheckColorBuffer(const Color &c) {
    auto w = _pDeviceAPI->PixelWidth();
    auto h = _pDeviceAPI->PixelHeight();
    for (int i = 0; i < h; i++)
    {
        bool begin = false;
        bool end = false;
        for (int j = 0; j < w; j++)
        {
            if (_colorBuffer[i * w + j] == c)
            {
                if (!begin)
                {
                    begin = true;
                }
                if (end)
                {
                    _colorBuffer[i * w + j] = Color(1, 0, 0, 1);
                    return false;
                }
            }
            else
            {
                if (begin)
                {
                    if (!end)
                    {
                        end = true;
                    }
                }
            }
        }
    }
    return true;
}

