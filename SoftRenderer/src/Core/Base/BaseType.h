#pragma once
#include <math.h>
#include <cfloat>
#include <assert.h>

#define SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define BREAK_IF(cond)           if(cond) break

#define PI 3.14159265f

float Angle2Rad(float angle);

struct Color {
	Color();
	Color(float _r, float _g, float _b, float _a=1.0f);

	bool operator==(const Color& right) const;
	bool operator!=(const Color& right) const;

	bool equals(const Color &other) const {
		return (*this == other);
	}

	unsigned int toInt() const {
		unsigned int ret = 0;
		ret |= ((int)(r * 255)) << 16;
		ret |= ((int)(g * 255)) << 8;
		ret |= ((int)(b * 255));
		return ret;
	}

	float r;
	float g;
	float b;
	float a;

	static const Color WHITE;
	static const Color YELLOW;
	static const Color BLUE;
	static const Color GREEN;
	static const Color RED;
	static const Color MAGENTA;
	static const Color BLACK;
	static const Color ORANGE;
	static const Color GRAY;
};

class Vector4f;
class Vector3f {
 public:

	static Vector3f Up;
	static Vector3f Right;
	static Vector3f Forward;

	Vector3f() : x(0.f), y(0.f), z(0.f) {}
	Vector3f(float inX, float inY, float inZ) {
		x = inX;
		y = inY;
		z = inZ;
	}
	explicit Vector3f(const float* array) {
		x = array[0];
		y = array[1];
		z = array[2];
	}
	void Set(float inX, float inY, float inZ) {
		x = inX;
		y = inY;
		z = inZ;
	}
	void Set(const float* array) {
		x = array[0];
		y = array[1];
		z = array[2];
	}
	void Normalize() {
		float l = Length();
		if (l > FLT_MIN) {
			x /= l;
			y /= l;
			z /= l;
		}
	}
	float Length() {
		return sqrtf(x*x + y*y + z*z);
	}

	Vector3f Cross(const Vector3f &p) {
		Vector3f ret;
		ret.x = y * p.z - p.y * z;
		ret.y = p.x * z - x * p.z;
		ret.z = x * p.y - p.x * y;
		return ret;
	}

	float Dot(const Vector3f &p) {
		float ret;
		ret = x * p.x + y * p.y + z * p.z;
		return ret;
	}

 public:
	float x, y, z;
};

<<<<<<< HEAD
class Vector4f {
public:
    Vector4f() : x(0.f), y(0.f), z(0.f), w(0.0f) {}
    Vector4f(float inX, float inY, float inZ, float inW) {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }
    Vector4f(const Vector3f& pos)
    {
        x = pos.x;
        y = pos.y;
        z = pos.z;
        w = 1.0f;
    }
    explicit Vector4f(const float* array) {
        x = array[0];
        y = array[1];
        z = array[2];
        w = array[3];
    }
    void Set(float inX, float inY, float inZ, float inW) {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }
    void Set(const float* array) {
        x = array[0];
        y = array[1];
        z = array[2];
        w = array[3];
    }
    
public:
    float x, y, z, w;
=======
struct Vector2f {
 public:
	Vector2f() : x(0.f), y(0.f) {}
	Vector2f(float inX, float inY) {
		x = inX;
		y = inY;
	}
	Vector2f(const Vector3f &p) {
		x = p.x;
		y = p.y;
	}
	explicit Vector2f(const float* array) {
		x = array[0];
		y = array[1];
	}
	void Set(float inX, float inY) {
		x = inX;
	}
	void Set(const float* array) {
		x = array[0];
		y = array[1];
	}

 public:
	float x, y;
};

struct Vector4f {
 public:
	Vector4f() : x(0.f), y(0.f), z(0.f), w(0.0f) {}
	Vector4f(float inX, float inY, float inZ, float inW) {
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}
	Vector4f(const Vector3f& pos) {
		x = pos.x;
		y = pos.y;
		z = pos.z;
		w = 1.0f;
	}
	explicit Vector4f(const float* array) {
		x = array[0];
		y = array[1];
		z = array[2];
		w = array[3];
	}
	void Set(float inX, float inY, float inZ, float inW) {
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}
	void Set(const float* array) {
		x = array[0];
		y = array[1];
		z = array[2];
		w = array[3];
	}

 public:
	float x, y, z, w;
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
};

class Vector2f {
 public:
    Vector2f() : x(0.f), y(0.f) {}
    Vector2f(float inX, float inY) {
        x = inX;
        y = inY;
    }
    Vector2f(const Vector3f &p)
    {
        x = p.x;
        y = p.y;
    }
    Vector2f(const Vector4f &p)
    {
        x = p.x;
        y = p.y;
    }
    explicit Vector2f(const float* array) {
        x = array[0];
        y = array[1];
    }
    void Set(float inX, float inY) {
        x = inX;
    }
    void Set(const float* array) {
        x = array[0];
        y = array[1];
    }

 public:
    float x, y;
};

struct Vertex {
	Vector4f pos;
	Color color;
	Vector3f normal;
<<<<<<< HEAD
    Vector2f uv;
    float w;//转换到投影空间下的w
    Vector2f screenPos;//屏幕空间
    Vertex(){}
    Vertex(const Vector4f& p, const Color& c)
    {
        pos = p;
        color = c;
    }
    Vertex(const Vector4f &p, const Color &c, const Vector2f &uv)
    {
        pos = p;
        color = c;
        this->uv = uv;
    }
};

struct Fragment : public Vertex {
    Fragment() {}
    Fragment(const Vector4f& p, const Color& c) : Vertex(p, c){}
=======
	Vector2f uv;
	Vertex() {}
	Vertex(const Vector3f& p, const Color& c) {
		pos = p;
		color = c;
	}
	Vertex(const Vector3f &p, const Color &c, const Vector2f &uv) {
		pos = p;
		color = c;
		this->uv = uv;
	}
};

struct Fragment : public Vertex {
	Fragment() {}
	Fragment(const Vector3f& p, const Color& c) : Vertex(p, c) {}
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
};

bool FloatEqual(float a, float b);
bool FloatIsZero(float a);
void AssertNotZero(float a);

int FloatCoord2IntLow(float v);
int FloatCoord2IntHigh(float v);

float Lerp(float from, float to, float percentage);

Color Lerp(const Color &from, const Color &to, float percentage);

Vector3f Lerp(const Vector3f &from, const Vector3f &to, float percentage);
Vector2f Lerp(const Vector2f &from, const Vector2f &to, float percentage);
Vector2f LerpUV(const Vector2f &from, float fromz, const Vector2f &to, float toz, float percentage);
Fragment Lerp(const Vertex &from, const Vertex &to, float percentage);

float Clamp(float min, float max, float v);
