#pragma once
#include "vector3D.h"

class Vector4D
{
public:
	Vector4D();
	Vector4D(float X,float Y,float Z, float W);
	Vector4D(const Vector4D& v);
	Vector4D(const Vector3D& v, float W = 1.0f);

	Vector4D Addition(const Vector4D& v) const;
	Vector4D Subtraction(const Vector4D& v) const;
	Vector4D ScalarMultiplication(const float& scalar) const;
	Vector4D ScalarDivision(const float& scalar) const;
	float Magnitude() const;
	float LengthSquared() const;
	void Normalize();
	void Homogenize();
	~Vector4D();

	Vector4D operator+(const Vector4D& v) const;
	Vector4D operator-(const Vector4D& v) const;
	Vector4D operator*(const float& scalar) const;
	Vector4D operator/(const float& scalar) const;

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;
};

std::ostream& operator<<(std::ostream& os, const Vector4D& v);