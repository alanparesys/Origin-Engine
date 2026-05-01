#include "Core/Maths/vector4D.h"
#include <cmath>
#include "Core/Debug/loader.h"

REGISTER_MODULE();

Vector4D::Vector4D()
{
	x = y = z = 0.f;
	w = 1.f;
}

Vector4D::Vector4D(float X, float Y, float Z, float W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

Vector4D::Vector4D(const Vector4D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

Vector4D::Vector4D(const Vector3D& v, float W)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = W;
}

Vector4D Vector4D::Addition(const Vector4D& v) const
{
	return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4D Vector4D::Subtraction(const Vector4D& v) const
{
	return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4D Vector4D::ScalarMultiplication(const float& scalar) const
{
	return Vector4D(x * scalar, y * scalar, z * scalar , w * scalar);
}

Vector4D Vector4D::ScalarDivision(const float& scalar) const
{
	if (scalar == 0.f)
		return *this;
	return Vector4D(x / scalar, y / scalar, z / scalar, w / scalar);
}

float Vector4D::Magnitude() const
{
	return sqrt(LengthSquared());
}

float Vector4D::LengthSquared() const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

void Vector4D::Normalize()
{
	float length = Magnitude();
	if (length == 0.f)
		return;
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

void Vector4D::Homogenize()
{
	if (w == 0)
		return;
	x /= w;
	y /= w;
	z /= w;
	w = 1.f;
}

Vector4D::~Vector4D()
{
}

Vector4D Vector4D::operator+(const Vector4D& v) const
{
	return Addition(v);
}

Vector4D Vector4D::operator-(const Vector4D& v) const
{
	return Subtraction(v);
}

Vector4D Vector4D::operator*(const float& scalar) const
{
	return ScalarMultiplication(scalar);
}

Vector4D Vector4D::operator/(const float& scalar) const
{
	return ScalarDivision(scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector4D& v)
{
	return os << "( " << v.x << " , " << v.y << " , " << v.z << " , " << v.w << " )";
}