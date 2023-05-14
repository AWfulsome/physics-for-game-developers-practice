#include "Matrix.hpp"

Matrix3x3::Matrix3x3(/* args */)
{
}

Vector Matrix3x3::operator * (const Vector &v) const
{
    return Vector(e11 * v.x + e12 * v.y + e13 * v.z,
                  e21 * v.x + e22 * v.y + e23 * v.z,
                  e31 * v.x + e32 * v.y + e33 * v.z);
}//Matrix3x3::operator *