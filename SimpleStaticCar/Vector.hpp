#include <ostream>

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

class Vector
{
public:
    double  x = 0;
    double  y = 0;
    double  z = 0;
    
    Vector() {};
    Vector(const double, const double, const double);

    double  Magnitude() const;
    void    Normalize();
    void    Reverse();

    Vector  operator - ();
    
    Vector& operator += (const Vector&);
    Vector& operator -= (const Vector&);
    Vector& operator *= (const double);
    Vector& operator /= (const double);

    Vector  operator + (const Vector&) const;
    Vector  operator - (const Vector&) const;
    Vector  operator * (const double) const;
    Vector  operator / (const double) const;

    double  operator * (const Vector&) const;    // Dot product
    Vector  operator ^ (const Vector&) const;    // Cross product
};

Vector operator * (const double, const Vector&);

std::ostream& operator << (std::ostream&, const Vector&);

#endif
