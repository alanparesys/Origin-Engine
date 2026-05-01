#include "Core/Maths/vector3D.h"
#include "Core/Maths/vector4D.h"
#include <cmath>
#include "Core/Maths/vector2D.h"
#include "Core/Debug/loader.h"

REGISTER_MODULE();

Vector3D::Vector3D()
{
	x = y = z = 0.f;
}

Vector3D::Vector3D(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

Vector3D::Vector3D(const Vector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3D::Vector3D(const Vector4D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3D Vector3D::Addition(const Vector3D& v) const
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::Subtraction(const Vector3D& v) const
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::ScalarMultiplication(const float& scalar) const
{
	return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::ScalarDivision(const float& scalar) const
{
	if (scalar == 0.f)
		return *this;
	return Vector3D(x / scalar, y / scalar, z / scalar);
}

Vector3D Vector3D::CrossProduct(const Vector3D& v) const
{
	float X = y * v.z - z * v.y;
	float Y = z * v.x - x * v.z;
	float Z = x * v.y - y * v.x;
	return Vector3D(X,Y,Z);
}

float Vector3D::DotProduct(const Vector3D& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

float Vector3D::Magnitude() const
{
	return sqrtf(LengthSquared());
}

float Vector3D::LengthSquared() const
{
	return (x * x) + (y * y) + (z * z);
}

void Vector3D::Normalize()
{
	float length = Magnitude();
	if (length == 0.f)
		return;
	x = x / length;
	y = y / length;
	z = z / length;
}

Vector3D::~Vector3D()
{
}

Vector3D Vector3D::operator+(const Vector3D& v) const
{
	return Addition(v);
}

Vector3D Vector3D::operator-(const Vector3D& v) const
{
	return Vector3D(Subtraction(v));
}

Vector3D Vector3D::operator*(const float& scalar) const
{
	return ScalarMultiplication(scalar);
}

Vector3D Vector3D::operator/(const float& scalar) const
{
	return ScalarDivision(scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v)
{
	return os << "( " << v.x << " , " << v.y << " , " << v.z << " )";
}