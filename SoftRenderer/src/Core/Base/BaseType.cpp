#include "BaseType.h"
#include <algorithm>

float Angle2Rad(float angle) {
	return angle * PI / 180.0f;
}

Vector3f Vector3f::Up(0.0f, 1.0f, 0.0f);
Vector3f Vector3f::Right(1.0f, 0.0f, 0.0f);
Vector3f Vector3f::Forward(0.0f, 0.0f, 1.0f);

Color::Color()
	: r(0.0f)
	, g(0.0f)
	, b(0.0f)
	, a(0.0f)
{}

Color::Color(float _r, float _g, float _b, float _a)
	: r(_r)
	, g(_g)
	, b(_b)
	, a(_a)
{}

bool Color::operator==(const Color& right) const {
	return (r == right.r && g == right.g && b == right.b && a == right.a);
}

bool Color::operator!=(const Color& right) const {
	return !(*this == right);
}

bool FloatEqual(float a, float b) {
	return fabs(a - b) <= FLT_MIN;
}

bool FloatIsZero(float a) {
	return FloatEqual(a, 0.0f);
}

void AssertNotZero(float a) {
	assert(!FloatIsZero(a));
}

<<<<<<< HEAD
int FloatCoord2IntLow(float v)
{
//    return (int)v-1;
    if (v - int(v) < 0.5f)
        return int(v);
    return int(v)+1;
}

int FloatCoord2IntHigh(float v)
{
//    return (int)v+1;
    if (v - int(v) >= 0.5f)
        return int(v)+1;
    return int(v);
}

float Lerp(float from, float to, float percentage) {
    return from + percentage * (to - from);
=======
int FloatCoord2IntLow(float v) {
	return (int)v;
	if (v - int(v) < 0.05f)
		return int(v)-1;
	return int(v)+1;
}

int FloatCoord2IntHigh(float v) {
	return (int)v;
	if (v - int(v) >= 0.05f)
		return int(v)+1;
	return int(v);
}

float Lerp(float from, float to, float percentage) {
	return (1 - percentage) * from + percentage * to;
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
}

Color Lerp(const Color &from, const Color &to, float percentage) {
	Color ret;
	ret.r = Lerp(from.r, to.r, percentage);
	ret.g = Lerp(from.g, to.g, percentage);
	ret.b = Lerp(from.b, to.b, percentage);
	ret.a = Lerp(from.a, to.a, percentage);
	return ret;
}

Vector3f Lerp(const Vector3f &from, const Vector3f &to, float percentage) {
	Vector3f ret;
	ret.x = Lerp(from.x, to.x, percentage);
	ret.y = Lerp(from.y, to.y, percentage);
	ret.z = Lerp(from.z, to.z, percentage);
	return ret;
}

Vector4f Lerp(const Vector4f &from, const Vector4f &to, float percentage) {
    Vector4f ret;
    ret.x = Lerp(from.x, to.x, percentage);
    ret.y = Lerp(from.y, to.y, percentage);
    ret.z = Lerp(from.z, to.z, percentage);
    ret.w = Lerp(from.w, to.w, percentage);
    return ret;
}

Vector2f Lerp(const Vector2f &from, const Vector2f &to, float percentage) {
	Vector2f ret;
	ret.x = Lerp(from.x, to.x, percentage);
	ret.y = Lerp(from.y, to.y, percentage);
	return ret;
}

<<<<<<< HEAD
Vector2f LerpUV(const Vector2f &from, float fw, const Vector2f &to, float tw, float percentage) {
    Vector2f ret;
    auto rfw = 1 / fw;
    auto rtw = 1 / tw;
    float lerpw = 1/Lerp(rfw, rtw, percentage);
    ret.x = Lerp(from.x * rfw, to.x * rtw, percentage) * lerpw;
    ret.y = Lerp(from.y * rfw, to.y * rtw, percentage) * lerpw;
//    if (ret.x < 0)
//        ret.x = 0;
//    if (ret.x > 1)
//        ret.x = 1;
//    if (ret.y < 0)
//        ret.y = 0;
//    if (ret.y > 1)
//        ret.y = 1;
    ret.x = Clamp(std::min(from.x, to.x), std::max(from.x, to.x), ret.x);
    ret.y = Clamp(std::min(from.y, to.y), std::max(from.y, to.y), ret.y);
    return ret;
=======
Vector2f LerpUV(const Vector2f &from, float fromz, const Vector2f &to, float toz, float percentage) {
	Vector2f ret;
	float z = Lerp(fromz, toz, percentage);
	ret.x = Lerp(from.x / fromz, to.x / toz, percentage) * z;
	ret.y = Lerp(from.y / fromz, to.y / toz, percentage) * z;
	return ret;
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
}

Fragment Lerp(const Vertex &from, const Vertex &to, float percentage) {
	Fragment ret;
	ret.pos = Lerp(from.pos, to.pos, percentage);
	ret.color = Lerp(from.color, to.color, percentage);
	ret.normal = Lerp(from.normal, to.normal, percentage);
<<<<<<< HEAD
    ret.uv = LerpUV(from.uv, from.pos.w, to.uv, to.pos.w, percentage);
    //ret.uv = Lerp(from.uv, to.uv, percentage);
=======
//    ret.uv = LerpUV(from.uv, from.pos.z, to.uv, to.pos.z, percentage);
	ret.uv = Lerp(from.uv, to.uv, percentage);
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
	return ret;
}

float Clamp(float min, float max, float v)
{
    if (v < min)
        return min;
    if (v > max)
        return max;
    return v;
}
