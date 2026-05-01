#include "Core/Maths/matrix4D.h"
#include <string>
#include "Core/Debug/loader.h"
using namespace std;
/// ____Column_Major_Matrix____ ///

REGISTER_MODULE();


Matrix4D::Matrix4D()
{
	for (int i = 0; i < 16; ++i)
		m[i] = 0;
}

Matrix4D::Matrix4D(std::vector<float> matrix)
{
	for (int i = 0; i < 16; ++i)
		m[i] = matrix[i];
}

Matrix4D::Matrix4D(Vector4D v, Vector4D v1, Vector4D v2, Vector4D v3)
{
	m[0] = v.x;
	m[1] = v1.x;
	m[2] = v2.x;
	m[3] = v3.x;
	m[4] = v.y;
	m[5] = v1.y;
	m[6] = v2.y;
	m[7] = v3.y;
	m[8] = v.z;
	m[9] = v1.z;
	m[10] = v2.z;
	m[11] = v3.z;
	m[12] = v.w;
	m[13] = v1.w;
	m[14] = v2.w;
	m[15] = v3.w;
}

Matrix4D Matrix4D::Multiplication(const Matrix4D& M) const
{
	Vector4D v1
	(
		m[0] * M.m[0] + m[1] * M.m[4] + m[2] * M.m[8] + m[3] * M.m[12],
		m[4] * M.m[0] + m[5] * M.m[4] + m[6] * M.m[8] + m[7] * M.m[12],
		m[8] * M.m[0] + m[9] * M.m[4] + m[10] * M.m[8] + m[11] * M.m[12],
		m[12] * M.m[0] + m[13] * M.m[4] + m[14] * M.m[8] + m[15] * M.m[12]
	);
	Vector4D v2
	(
		m[0] * M.m[1] + m[1] * M.m[5] + m[2] * M.m[9] + m[3] * M.m[13],
		m[4] * M.m[1] + m[5] * M.m[5] + m[6] * M.m[9] + m[7] * M.m[13],
		m[8] * M.m[1] + m[9] * M.m[5] + m[10] * M.m[9] + m[11] * M.m[13],
		m[12] * M.m[1] + m[13] * M.m[5] + m[14] * M.m[9] + m[15] * M.m[13]
	);
	Vector4D v3
	(
		m[0] * M.m[2] + m[1] * M.m[6] + m[2] * M.m[10] + m[3] * M.m[14],
		m[4] * M.m[2] + m[5] * M.m[6] + m[6] * M.m[10] + m[7] * M.m[14],
		m[8] * M.m[2] + m[9] * M.m[6] + m[10] * M.m[10] + m[11] * M.m[14],
		m[12] * M.m[2] + m[13] * M.m[6] + m[14] * M.m[10] + m[15] * M.m[14]
	);
	Vector4D v4
	(
		m[0] * M.m[3] + m[1] * M.m[7] + m[2] * M.m[11] + m[3] * M.m[15],
		m[4] * M.m[3] + m[5] * M.m[7] + m[6] * M.m[11] + m[7] * M.m[15],
		m[8] * M.m[3] + m[9] * M.m[7] + m[10] * M.m[11] + m[11] * M.m[15],
		m[12] * M.m[3] + m[13] * M.m[7] + m[14] * M.m[11] + m[15] * M.m[15]
	);

	return Matrix4D(v1,v2,v3,v4);
}

Vector4D Matrix4D::Multiplication(const Vector4D& v) const
{
	Vector4D newVector;
	newVector.x = v.x * m[0] + v.y  * m[1]  + v.z * m[2]  + v.w * m[3];
	newVector.y = v.x * m[4] + v.y  * m[5]  + v.z * m[6]  + v.w * m[7];
	newVector.z = v.x * m[8] + v.y  * m[9]  + v.z * m[10] + v.w * m[11];
	newVector.w = v.x * m[12] + v.y * m[13] + v.z * m[14] + v.w * m[15];
	return newVector;
}

Matrix4D Matrix4D::GetInverse() const
{
    Matrix4D inv;

    inv.m[0] = m[5] * m[10] * m[15] -
        m[5] * m[11] * m[14] -
        m[9] * m[6] * m[15] +
        m[9] * m[7] * m[14] +
        m[13] * m[6] * m[11] -
        m[13] * m[7] * m[10];

    inv.m[4] = -m[4] * m[10] * m[15] +
        m[4] * m[11] * m[14] +
        m[8] * m[6] * m[15] -
        m[8] * m[7] * m[14] -
        m[12] * m[6] * m[11] +
        m[12] * m[7] * m[10];

    inv.m[8] = m[4] * m[9] * m[15] -
        m[4] * m[11] * m[13] -
        m[8] * m[5] * m[15] +
        m[8] * m[7] * m[13] +
        m[12] * m[5] * m[11] -
        m[12] * m[7] * m[9];

    inv.m[12] = -m[4] * m[9] * m[14] +
        m[4] * m[10] * m[13] +
        m[8] * m[5] * m[14] -
        m[8] * m[6] * m[13] -
        m[12] * m[5] * m[10] +
        m[12] * m[6] * m[9];

    inv.m[1] = -m[1] * m[10] * m[15] +
        m[1] * m[11] * m[14] +
        m[9] * m[2] * m[15] -
        m[9] * m[3] * m[14] -
        m[13] * m[2] * m[11] +
        m[13] * m[3] * m[10];

    inv.m[5] = m[0] * m[10] * m[15] -
        m[0] * m[11] * m[14] -
        m[8] * m[2] * m[15] +
        m[8] * m[3] * m[14] +
        m[12] * m[2] * m[11] -
        m[12] * m[3] * m[10];

    inv.m[9] = -m[0] * m[9] * m[15] +
        m[0] * m[11] * m[13] +
        m[8] * m[1] * m[15] -
        m[8] * m[3] * m[13] -
        m[12] * m[1] * m[11] +
        m[12] * m[3] * m[9];

    inv.m[13] = m[0] * m[9] * m[14] -
        m[0] * m[10] * m[13] -
        m[8] * m[1] * m[14] +
        m[8] * m[2] * m[13] +
        m[12] * m[1] * m[10] -
        m[12] * m[2] * m[9];

    inv.m[2] = m[1] * m[6] * m[15] -
        m[1] * m[7] * m[14] -
        m[5] * m[2] * m[15] +
        m[5] * m[3] * m[14] +
        m[13] * m[2] * m[7] -
        m[13] * m[3] * m[6];

    inv.m[6] = -m[0] * m[6] * m[15] +
        m[0] * m[7] * m[14] +
        m[4] * m[2] * m[15] -
        m[4] * m[3] * m[14] -
        m[12] * m[2] * m[7] +
        m[12] * m[3] * m[6];

    inv.m[10] = m[0] * m[5] * m[15] -
        m[0] * m[7] * m[13] -
        m[4] * m[1] * m[15] +
        m[4] * m[3] * m[13] +
        m[12] * m[1] * m[7] -
        m[12] * m[3] * m[5];

    inv.m[14] = -m[0] * m[5] * m[14] +
        m[0] * m[6] * m[13] +
        m[4] * m[1] * m[14] -
        m[4] * m[2] * m[13] -
        m[12] * m[1] * m[6] +
        m[12] * m[2] * m[5];

    inv.m[3] = -m[1] * m[6] * m[11] +
        m[1] * m[7] * m[10] +
        m[5] * m[2] * m[11] -
        m[5] * m[3] * m[10] -
        m[9] * m[2] * m[7] +
        m[9] * m[3] * m[6];

    inv.m[7] = m[0] * m[6] * m[11] -
        m[0] * m[7] * m[10] -
        m[4] * m[2] * m[11] +
        m[4] * m[3] * m[10] +
        m[8] * m[2] * m[7] -
        m[8] * m[3] * m[6];

    inv.m[11] = -m[0] * m[5] * m[11] +
        m[0] * m[7] * m[9] +
        m[4] * m[1] * m[11] -
        m[4] * m[3] * m[9] -
        m[8] * m[1] * m[7] +
        m[8] * m[3] * m[5];

    inv.m[15] = m[0] * m[5] * m[10] -
        m[0] * m[6] * m[9] -
        m[4] * m[1] * m[10] +
        m[4] * m[2] * m[9] +
        m[8] * m[1] * m[6] -
        m[8] * m[2] * m[5];
    
    float det = m[0] * inv.m[0] + m[1] * inv.m[4] + m[2] * inv.m[8] + m[3] * inv.m[12];

    if (det == 0)
        return Matrix4D();

    det = 1.0f / det;

    for (int i = 0; i < 16; i++)
        inv.m[i] *= det;

    return inv;

}

Matrix4D::~Matrix4D()
{

}

Vector4D Matrix4D::operator*(const Vector4D& v) const
{
	return Multiplication(v);
}

Matrix4D Matrix4D::operator*(const Matrix4D& M) const
{
	return Multiplication(M);
}

ostream& operator<<(ostream& os, const Matrix4D& M)
{
	string chain;
	for (int i = 0; i < 16; ++i)
	{
		if (i % 4 == 0 && i != 0)
			chain += ")\n( ";
		else if (i == 0)
		{
			chain += "( ";
		}
		chain += to_string(M.m[i]) + " ";

	}
	chain += ")";


	return os << chain;
}