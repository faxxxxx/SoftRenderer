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
    enum FilterType {
        Point,
        Bilinear,
        Trilinear
    };
    
    Texture() {}
    void Load(const std::string& path);
    Color GetColor(const Vector2f &uv, FilterType filter=Bilinear);
    
    Color Sample(int x, int y);
    png_datap _data = new png_data_t();
};
