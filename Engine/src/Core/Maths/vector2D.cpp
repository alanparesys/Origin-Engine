#include "Core/Maths/vector2D.h"
#include <cmath>
#include "Core/Debug/loader.h"

REGISTER_MODULE();

Vector2D::Vector2D()
{
	x = y = 0.f;
}

Vector2D::Vector2D(float X, float Y)
{
	x = X;
	y = Y;
}

Vector2D::Vector2D(const Vector2D& v)
{
	x = v.x;
	y = v.y;
}

Vector2D Vector2D::Addition(const Vector2D& v) const
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::Substraction(const Vector2D& v) const
{
	return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::ScalarMultiplication(const float& scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::ScalarDivision(const float& scalar) const
{
	return Vector2D(x / scalar, y / scalar);
}

float Vector2D::CrossProduct(const Vector2D& v) const
{
	return x * v.y - v.x * y;
}

float Vector2D::DotProduct(const Vector2D& v) const
{
	return x * v.x + y * v.y;
}

float Vector2D::Magnitude() const
{
	return sqrtf(LengthSquared());
}

float Vector2D::LengthSquared() const
{
	return x * x + y * y;
}

void Vector2D::Normalize()
{
	float length = Magnitude();
	x /= length;
	y /= length;
}

Vector2D::~Vector2D()
{

}

Vector2D Vector2D::operator+(const Vector2D& v) const
{
	return Addition(v);
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	return Substraction(v);
}

Vector2D Vector2D::operator*(const float& scalar) const
{
	return ScalarMultiplication(scalar);
}

Vector2D Vector2D::operator/(const float& scalar) const
{
	return ScalarDivision(scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v)
{
	return os << "( " << v.x << " , " << v.y << " )";
}
