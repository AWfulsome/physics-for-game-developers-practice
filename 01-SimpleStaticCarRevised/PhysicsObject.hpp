#include <string>
#include <vector>

#include "Matrix.hpp"
#include "Vector.hpp"

#ifndef PHYSICS_OBJECT_HPP_
#define PHYSICS_OBJECT_HPP_

class Object3D
{
public:
    std::string name = "";

    Object3D() {}
    Object3D(const double mass, const Vector &centerOfGravity = Vector(0, 0, 0), const Matrix3x3 &inertiaTensor = Matrix3x3::IDENTITY);

    double  get_mass() const;
    Vector  get_center_of_gravity() const;
    Vector  get_corrected_center_of_gravity() const;
    Vector  get_moments_of_inertia() const;
    Vector  get_corrected_moments_of_inertia() const;
    Matrix3x3   get_inertia_tensor() const;
    Matrix3x3   get_corrected_inertia_tensor() const;

protected:
    double  mass_;
    Vector  centerOfGravity_ = Vector(0, 0, 0);
    Vector  correctedCenterOfGravity_ = Vector(0, 0, 0);
    Matrix3x3   inertiaTensor_ = Matrix3x3::IDENTITY;
    Matrix3x3   correctedInertiaTensor_ = Matrix3x3::IDENTITY;

    void    update_corrected_center_of_gravity(const Vector& combinedCenterOfGravity);
    void    update_corrected_inertia_tensor(const Vector& combinedMomentsOfInertia);

    friend class ObjectGroup3D;
};

class PointMass : public Object3D
{
public:
    PointMass() {}
    PointMass(const double mass, const Vector &centerOfGravity = Vector(0, 0, 0));
};

class RectangularCylinder : public Object3D
{
public:
    RectangularCylinder() {}
    RectangularCylinder(const double mass, const double xLength, const double yLength, const double zLength, const Vector &centerOfGravity = Vector(0, 0, 0));

private:
    double  xLength_ = 0;
    double  yLength_ = 0;
    double  zLength_ = 0;
};

class ObjectGroup3D
{
public:
    ObjectGroup3D() {}

    std::size_t get_number_of_components() const;
    double  get_total_mass() const;
    Vector  get_center_of_gravity() const;
    Vector  get_moments_of_inertia() const;

    Object3D    get_component(int index) const;
    void    add_component(const Object3D &component);
    // Object3D    remove_component(int) const;

private:
    double  totalMass_ = 0;
    std::vector<Object3D>   components_;
    Vector  combinedCenterOfGravity_ = Vector(0, 0, 0);
    Matrix3x3   combinedInertiaTensor_ = Matrix3x3();

    void    update_combined_center_of_gravity();
    void    update_combined_inertia_tensor();
};

#endif