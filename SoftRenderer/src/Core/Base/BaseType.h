#pragma once

#define SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define BREAK_IF(cond)           if(cond) break

#define PI 3.14159265f

struct Color {
	Color();
	Color(float _r, float _g, float _b, float _a);

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

struct Vector4f {
 public:
	Vector4f() : x(0.f), y(0.f), z(0.f), w(0.0f) {}
	Vector4f(float inX, float inY, float inZ, float inW) {
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
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
};

struct Vector3f {
 public:
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

 public:
	float x, y, z;
};

struct Vector2f {
 public:
	Vector2f() : x(0.f), y(0.f) {}
	Vector2f(float inX, float inY) {
		x = inX;
		y = inY;
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
	Vector3f pos;
	Color color;
	Vector3f normal;
};

struct Triangle {
	Vertex verts[3];
};

struct Fragment : public Vertex {

};

Triangle CreateTri(Vertex v1, Vertex v2, Vertex v3);

float Lerp(float from, float to, float percentage);

Color Lerp(const Color &from, const Color &to, float percentage);

Vector3f Lerp(const Vector3f &from, const Vector3f &to, float percentage);

Fragment Lerp(const Vertex &from, const Vertex &to, float percentage);