#include <string>
#include <vector>

#include "Vector.hpp"

#ifndef PHYSICS_OBJECT_HPP_
#define PHYSICS_OBJECT_HPP_

class PointMass
{
public:
    double  mass = 0;
    Vector  designPosition = Vector(0, 0, 0);
    Vector  correctedPosition = Vector(0, 0, 0);
    
    PointMass() {}
    PointMass(const double mass_, const Vector &designPosition_ = Vector(0, 0, 0), const Vector &correctedPosition_ = Vector(0, 0, 0));
};

class Object3D
{
public:
    std::string name = "";

    Object3D() {}
    Object3D(const double mass, const Vector &centerOfGravity = Vector(0, 0, 0), const Vector &momentsOfInertia = Vector(1, 1, 1));

    double  get_mass() const;
    Vector  get_center_of_gravity() const;
    Vector  get_moments_of_inertia() const;

protected:
    double  mass_;
    Vector  centerOfGravity_ = Vector(0, 0, 0);
    Vector  momentsOfInertia_ = Vector(1, 1, 1);
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
    void    update_moment_of_inertia();
};

class ObjectGroup3D
{
public:
    ObjectGroup3D() {}

    std::size_t get_number_of_components() const;
    double  get_total_mass() const;
    Vector  get_center_of_gravity() const;
    Vector  get_moments_of_inertia() const;

    Object3D    get_component(int) const;
    void    add_component(Object3D);
    // Object3D    remove_component(int) const;

private:
    double  totalMass_ = 0;
    Vector  combinedCenterOfGravity_ = Vector(0, 0, 0);
    Vector  combinedMomentsOfInertia_ = Vector(1, 1, 1);
    std::vector<Object3D>   components_;

    void    update_combined_center_of_gravity();
    void    update_combined_moments_of_inertia();
};

#endif