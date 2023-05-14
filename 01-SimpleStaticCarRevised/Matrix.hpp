#include "Vector.hpp"

class Matrix3x3
{
public:
    static const Matrix3x3  IDENTITY;
    static const Matrix3x3  ZERO;

    double e11 = 0, e12 = 0, e13 = 0;
    double e21 = 0, e22 = 0, e23 = 0;
    double e31 = 0, e32 = 0, e33 = 0;

    Matrix3x3();
    Matrix3x3(const double e11_, const double e12_, const double e13_,
              const double e21_, const double e22_, const double e23_,
              const double e31_, const double e32_, const double e33_);
    
    Vector operator * (const Vector&) const;
    
    Matrix3x3& operator += (const Matrix3x3&);
};