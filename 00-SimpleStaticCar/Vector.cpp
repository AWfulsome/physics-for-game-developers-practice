#include "Vector.hpp"

Vector::Vector(const double x_, const double y_, const double z_): x(x_), y(y_), z(z_) { }

// double Vector::Magnitude() const;
// void Vector::Normalize();
// void Vector::Reverse();

// Vector Vector::operator - ();

Vector& Vector::operator += (const Vector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}//Vector::operator +=

// Vector& Vector::operator -= (const Vector&);
// Vector& Vector::operator *= (const double);
// Vector& Vector::operator /= (const double);

Vector Vector::operator + (const Vector &v) const
{
    return Vector(x + v.x, y + v.y, z + v.z);
}//Vector::operator +

Vector Vector::operator - (const Vector &v) const
{
    return Vector(x - v.x, y - v.y, z - v.z);
}//Vector::operator -

Vector Vector::operator * (const double c) const
{
    return Vector(c * x, c * y, c * z);
}//Vector::operator *

Vector Vector::operator / (const double c) const
{
    return *this * (1 / c);
}//Vector::operator /

// double Vector::operator * (const Vector&) const;
// Vector Vector::operator ^ (const Vector&) const;

Vector operator * (const double c, const Vector &v)
{
    return v * c;
}//operator *

std::ostream& operator << (std::ostream &os, const Vector &vec)
{
    os << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
    return os;
}//operator <<