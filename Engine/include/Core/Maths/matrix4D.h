#pragma once
#include "vector4D.h"
#include "vector3D.h"
#include <iostream>
#include <vector>
#include <cmath>

inline constexpr double PI = 3.14159265358979323846;

class Matrix4D
{
public:
	Matrix4D();
	Matrix4D(std::vector<float> matrix);
	Matrix4D(Vector4D v, Vector4D v1, Vector4D v2, Vector4D v3);
	Matrix4D Multiplication(const Matrix4D& M) const;
	Vector4D Multiplication(const Vector4D& v) const;
	Matrix4D GetInverse() const;

	~Matrix4D();

	Vector4D operator*(const Vector4D& v) const;
	Matrix4D operator*(const Matrix4D& M) const;

	float m[16];

	static Matrix4D Identity()
	{
		return Matrix4D
		(
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			}
		);
	}

	static Matrix4D CreateTransformMatrix(const Vector3D& rotation, const Vector3D& position, const Vector3D& scale)
	{
		float cx = cosf((float)rotation.x);
		float sx = sinf((float)rotation.x);
		float cy = cosf((float)rotation.y);
		float sy = sinf((float)rotation.y);
		float cz = cosf((float)rotation.z);
		float sz = sinf((float)rotation.z);

		float r00 = cy * cz;
		float r01 = cz * sx * sy - cx * sz;
		float r02 = sx * sz + cx * cz * sy;

		float r10 = cy * sz;
		float r11 = cx * cz + sx * sy * sz;
		float r12 = cx * sy * sz - cz * sz;

		float r20 = -sy;
		float r21 = cy * sx;
		float r22 = cx * cy;

		r00 *= scale.x; r01 *= scale.y; r02 *= scale.z;
		r10 *= scale.x; r11 *= scale.y; r12 *= scale.z;
		r20 *= scale.x; r21 *= scale.y; r22 *= scale.z;

		return Matrix4D
		(
			Vector4D(r00, r01, r02, position.x),
			Vector4D(r10, r11, r12, position.y),
			Vector4D(r20, r21, r22, position.z),
			Vector4D(0, 0, 0, 1)
		);
	}

	static Matrix4D CreatePerspectiveProjectionMatrix(unsigned int width, unsigned int height, float nearVal, float farVal, float fov)
	{
		float scale = tanf(fov * 0.5f * (float)PI / 180.f) * nearVal;
		float aspect = (float)width / (float)height;
		float r = aspect * scale; float l = -r;
		float t = scale; float b = -t;

		Vector4D v1(2.f * nearVal / (r - l), 0.f, 0.f, 0.f);
		Vector4D v2(0.f, 2.f * nearVal / (t - b), 0.f, 0.f);
		Vector4D v3((r + l) / (r - l), (t + b) / (t - b), -(farVal + nearVal) / (farVal - nearVal), -1.f);
		Vector4D v4(0.f, 0.f, -2.f * farVal * nearVal / (farVal - nearVal), 0.f);

		return Matrix4D(v1, v2, v3, v4);
	}
};

std::ostream& operator<<(std::ostream& os, const Matrix4D& M);