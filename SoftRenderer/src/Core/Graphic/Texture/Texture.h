#pragma once
#include <string>
#include "Core/Base/BaseType.h"

typedef struct png_data_t {
    unsigned int width;
    unsigned int height;
    unsigned char* data;
}  *png_datap;


class Texture {
public:
    Texture() {}
    void Load(const std::string& path);
    Color GetColor(const Vector2f &uv);
    
    png_datap _data = new png_data_t();
};
