#pragma once
#include "SDL.h"
#include "Core/Base/BaseType.h"

class IDeviceAPI {
 public:
	virtual ~IDeviceAPI() {}
	virtual void DrawPixel(int x, int y, const Color & color) = 0;
	virtual void DrawPixel(const Vector2f &pos, const Color & color) = 0;
	virtual void DrawLine(const Vector2f &from, const Vector2f &to, const Color & color) = 0;
	virtual int PixelWidth() = 0;
	virtual int PixelHeight() = 0;
};

class DeviceAPI : public IDeviceAPI {
 public:
	static DeviceAPI * Create(SDL_Window *pWindow);
	virtual void DrawPixel(int x, int y, const Color & color) override;
	virtual void DrawPixel(const Vector2f &pos, const Color & color) override;
	virtual void DrawLine(const Vector2f &from, const Vector2f &to, const Color & color) override;
	virtual int PixelWidth() override;
	virtual int PixelHeight() override;

	void BeginRender();
	void Clear();
	void EndRender();

 private:
	DeviceAPI() {}
	bool Init(SDL_Window *pWindow);

 private:
	SDL_Surface * _pSurface = nullptr;
	SDL_Surface *_pBackSurface = nullptr;
	SDL_Window *_pWindow = nullptr;
};