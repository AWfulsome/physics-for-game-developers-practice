#include "Vector.hpp"

class Matrix3x3
{
private:
    double e11 = 0, e12 = 0, e13 = 0;
    double e21 = 0, e22 = 0, e23 = 0;
    double e31 = 0, e32 = 0, e33 = 0;

public:
    Matrix3x3();

    Vector operator * (const Vector&) const;
};