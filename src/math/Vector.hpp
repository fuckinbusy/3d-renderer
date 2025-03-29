#pragma once
#include <cmath>

struct Vec3
{
	float x, y, z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vec3 operator+(const Vec3& v) const { return { x + v.x, y + v.y, z + v.z }; }
	Vec3 operator-(const Vec3& v) const { return { x - v.x, y - v.y, z - v.z }; }
	Vec3 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }

	float Length() const { return std::sqrt(x * x + y * y + z * z); }
	Vec3 Normalize() const { float l = Length(); return { x / l , y / l, z / l }; }
};

struct Vec4
{
	float x, y, z, w;

	Vec4() : x(0), y(0), z(0), w(1) {}
	Vec4(float x, float y, float z, float w = 1) : x(x), y(y), z(z), w(w) {}
};