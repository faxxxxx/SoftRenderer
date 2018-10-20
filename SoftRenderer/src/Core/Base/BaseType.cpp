#include "BaseType.h"

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

float Lerp(float from, float to, float percentage) {
	return from + (to - from) * percentage;
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

Vertex Lerp(const Vertex &from, const Vertex &to, float percentage) {
	Vertex ret;
	ret.pos = Lerp(from.pos, to.pos, percentage);
	ret.color = Lerp(from.color, to.color, percentage);
	ret.normal = Lerp(from.normal, to.normal, percentage);
	return ret;
}