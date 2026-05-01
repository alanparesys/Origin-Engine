#pragma once
#include <iostream>

class Vector4D;
class Vector3D
{
public:
	Vector3D();
	Vector3D(float X, float Y, float Z);
	Vector3D(const Vector3D& v);
	Vector3D(const Vector4D& v);
	
	Vector3D Addition(const Vector3D& v) const;
	Vector3D Subtraction(const Vector3D& v) const;
	Vector3D ScalarMultiplication(const float& scalar) const;
	Vector3D ScalarDivision(const float& scalar) const;
	Vector3D CrossProduct(const Vector3D& v) const;
	float DotProduct(const Vector3D& v) const;
	float Magnitude() const;
	float LengthSquared() const;
	void Normalize();
	~Vector3D();

	Vector3D operator+(const Vector3D& v) const;
	Vector3D operator-(const Vector3D& v) const;
	Vector3D operator*(const float& scalar) const;
	Vector3D operator/(const float& scalar) const;

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};

std::ostream& operator<<(std::ostream& os, const Vector3D& v);