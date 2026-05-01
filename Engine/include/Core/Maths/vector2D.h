#pragma once
#include <iostream>

class Vector2D
{
public:
	Vector2D();
	Vector2D(float X,float Y);
	Vector2D(const Vector2D& v);

	Vector2D Addition(const Vector2D& v) const;
	Vector2D Substraction(const Vector2D& v) const;
	Vector2D ScalarMultiplication(const float& scalar) const;
	Vector2D ScalarDivision(const float& scalar) const;
	float CrossProduct(const Vector2D& v) const;
	float DotProduct(const Vector2D& v) const;
	float Magnitude() const;
	float LengthSquared() const;
	void Normalize();
	~Vector2D();

	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator*(const float& scalar) const;
	Vector2D operator/(const float& scalar) const;

	float x = 0.f;
	float y = 0.f;
};

std::ostream& operator<<(std::ostream& os, const Vector2D& v);