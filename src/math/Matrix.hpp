#pragma once
#include <numbers>
#include "Vector.hpp"

/*	MATRIX REPRESENTATION
* 
* 
*	   x  y  z  w
*	x |1  0  0  0| x
*	y |0  1  0  0| y
*	z |0  0	 1	0| z
*	w |0  0	 0	1| w
*	   x  y  z  w
* 
* 
*/

struct Mat4
{
	float m[4][4];

	Mat4()
	{
		for (char i = 0; i < 4; i++)
			for (char j = 0; j < 4; j++)
				m[i][j] = (i == j) ? 1.0f : 0.0f;
	}

	Mat4 operator*(const Mat4& other) const {
		Mat4 result;

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result.m[i][j] = 0;
				for (int k = 0; k < 4; ++k) {
					result.m[i][j] += this->m[i][k] * other.m[k][j];
				}
			}
		}

		return result;
	}

	Vec3 operator*(const Vec3& v) const
	{
		return {
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]
		};
	}
};

struct Mat4Scale : public Mat4
{
	Mat4Scale() : Mat4() {}

	inline void Update(float sx, float sy, float sz)
	{
		m[0][0] = sx;
		m[1][1] = sy;
		m[2][2] = sz;
	}

	inline void Update(float scale)
	{
		m[0][0] = scale;
		m[1][1] = scale;
		m[2][2] = scale;
	}

	Vec3 operator*(const Vec3& v) const
	{
		return {
			v.x * m[0][0],
			v.y * m[1][1],
			v.z * m[2][2]
		};
	}
};

struct Mat4Translate : public Mat4
{
	Mat4Translate() : Mat4() {}

	Vec3 operator*(const Vec3& v) const
	{
		return {
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]
		};
	}

	inline void Update(float tx, float ty, float tz)
	{
		m[3][0] = tx;
		m[3][1] = ty;
		m[3][2] = tz;
	}
};

struct Mat4Projection : public Mat4
{
	Mat4Projection() : Mat4() {}

	Vec3 operator*(const Vec3& v) const
	{
		Vec3 r{};
		float w;

		r.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
		r.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
		r.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
		w   = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];

		if (w != 0.0f)
		{
			r.x /= w;
			r.y /= w;
			r.z /= w;
		}

		return r;
	}

	inline void Update(float aspect, float fov, float n, float f)
	{
		float rfov = 1 / tanf(fov * 0.5f * (std::numbers::pi / 180.0f));
		m[0][0] = rfov / aspect;
		m[1][1] = rfov;
		m[2][2] = (f + n) / (n - f);
		m[2][3] = (2 * f * n) / (n - f);
		m[3][2] = -1.0f;
	}
};

struct Mat4Rotation : public Mat4
{
	Mat4Rotation() : Mat4() {}

	Vec3 operator*(const Vec3& v) const
	{
		return { 
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]
		};
	}

	inline Mat4 MatrixRotation(float angleX, float angleY, float angleZ) {
		Mat4 rotX, rotY, rotZ;

		float cx = cos(angleX), sx = sin(angleX);
		rotX.m[0][0] = 1;  rotX.m[1][1] = cx;  rotX.m[1][2] = -sx;
		rotX.m[2][1] = sx; rotX.m[2][2] = cx;  rotX.m[3][3] = 1;

		float cy = cos(angleY), sy = sin(angleY);
		rotY.m[0][0] = cy;  rotY.m[0][2] = sy;
		rotY.m[1][1] = 1;
		rotY.m[2][0] = -sy; rotY.m[2][2] = cy;  rotY.m[3][3] = 1;

		float cz = cos(angleZ), sz = sin(angleZ);
		rotZ.m[0][0] = cz;  rotZ.m[0][1] = -sz;
		rotZ.m[1][0] = sz;  rotZ.m[1][1] = cz;  rotZ.m[2][2] = 1;
		rotZ.m[3][3] = 1;

		return rotZ * rotY * rotX;
	}
};