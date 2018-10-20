#include "DeviceAPI.h"
#include "../../Base/BaseType.h"
#include <iostream>
#include <cfloat>

DeviceAPI * DeviceAPI::Create(SDL_Window * pWindow) {
	DeviceAPI *ret = new DeviceAPI();
	if (ret != nullptr && ret->Init(pWindow)) {
		return ret;
	}
	SAFE_DELETE(ret);
	return nullptr;
}

int SD_ClearBackSurface(SDL_Surface *pSurface, uint32_t color) {
	SDL_FillRect(pSurface, NULL, color);
	return 1;
}
int SD_Flip(SDL_Surface *pBackSurface, SDL_Surface *pSurface, SDL_Window *pWindow) {
	SDL_BlitSurface(pBackSurface, NULL, pSurface, NULL);
	SDL_UpdateWindowSurface(pWindow);
	return 1;
}

void DeviceAPI::DrawPixel(int x, int y, const Color & color) {
	int lpitch = (_pBackSurface->pitch >> 2);
	uint32_t* video_buffer = (uint32_t*)_pBackSurface->pixels;
	video_buffer[x + y * lpitch] = color.toInt();
}

void DeviceAPI::DrawPixel(const Vector2f & pos, const Color & color) {
	DrawPixel((int)pos.x, (int)pos.y, color);
}

void DeviceAPI::DrawLine(const Vector2f &from, const Vector2f &to, const Color & color) {
	int fx = (int)from.x;
	int fy = (int)from.y;
	int tx = (int)to.x;
	int ty = (int)to.y;

	int dx = tx - fx;
	int dy = ty - fy;
	float k = 0.0f;
	bool inverse = false;

	if (abs(dx) > FLT_MIN) {
		k = (float)dy / dx;
	}

	//dx等于0，k还是大于1，需要翻转坐标系
	if (abs(k) > 1 || abs(dx) <= FLT_MIN) {
		std::swap(fx, fy);
		std::swap(tx, ty);
		std::swap(dx, dy);
		k = (float)dy / dx;
		inverse = true;
	}

	//x从小到大
	if (fx > tx) {
		std::swap(fx, tx);
		std::swap(fy, ty);
		dx = -dx;
		dy = -dy;
	}

	float e = 0.0f;
	int x = fx;
	int y = fy;
	bool iterate = (abs(k) > FLT_MIN);
	for (int i = 0; i < dx; i++) {
		if (!inverse)
			DrawPixel(x, y, color);
		else
			DrawPixel(y, x, color);
		x++;
		if (iterate) {
			e += k;
			if (k > 0) {
				if (e >= 0) {
					y++;
					e -= 1;
				}
			} else {
				if (e <= 0) {
					y--;
					e += 1;
				}
			}
		}
	}
}

int DeviceAPI::PixelWidth() {
	return _pBackSurface->w;
}

int DeviceAPI::PixelHeight() {
	return _pBackSurface->h;
}

bool DeviceAPI::Init(SDL_Window * pWindow) {
	bool ret = false;
	do {
		if (!pWindow) {
			break;
		}
		_pWindow = pWindow;

		_pSurface = SDL_GetWindowSurface(pWindow);
		_pBackSurface = SDL_CreateRGBSurface(0, _pSurface->w, _pSurface->h, 32, 0, 0, 0, 0);
		if (!_pSurface || !_pBackSurface) {
			std::cout << "Create surface fail !" << std::endl;
			break;
		}
		ret = true;
	} while (0);
	return ret;
}

void DeviceAPI::BeginRender() {
	Clear();
	SDL_LockSurface(_pBackSurface);
}

void DeviceAPI::Clear() {
	SD_ClearBackSurface(_pBackSurface, 0);
}

void DeviceAPI::EndRender() {
	SDL_UnlockSurface(_pBackSurface);
	SD_Flip(_pBackSurface, _pSurface, _pWindow);
}