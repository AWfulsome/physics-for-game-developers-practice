#include "Matrix.hpp"

const Matrix3x3 Matrix3x3::IDENTITY = Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);
const Matrix3x3 Matrix3x3::ZERO = Matrix3x3();

Matrix3x3::Matrix3x3() {}

Matrix3x3::Matrix3x3(const double e11_, const double e12_, const double e13_,
                     const double e21_, const double e22_, const double e23_,
                     const double e31_, const double e32_, const double e33_):
    e11(e11_), e12(e12_), e13(e13_),
    e21(e21_), e22(e22_), e23(e23_),
    e31(e31_), e32(e32_), e33(e33_) {}

Vector Matrix3x3::operator * (const Vector &v) const
{
    return Vector(e11 * v.x + e12 * v.y + e13 * v.z,
                  e21 * v.x + e22 * v.y + e23 * v.z,
                  e31 * v.x + e32 * v.y + e33 * v.z);
}//Matrix3x3::operator *

Matrix3x3& Matrix3x3::operator += (const Matrix3x3& matrix)
{
    e11 += matrix.e11, e12 += matrix.e12, e13 += matrix.e13;
    e21 += matrix.e21, e22 += matrix.e22, e23 += matrix.e23;
    e31 += matrix.e31, e32 += matrix.e32, e33 += matrix.e33;
    return *this;
}//Matrix3x3::operator +=