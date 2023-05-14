#include "PhysicsObject.hpp"
#include "Vector.hpp"

PointMass::PointMass(const double mass_, const Vector &dP_, const Vector &cP_):
    mass(mass_), designPosition(dP_), correctedPosition(cP_) {}

Object3D::Object3D(const double mass, const Vector &centerOfGravity, const Vector &momentsOfInertia):
    mass_(mass), centerOfGravity_(centerOfGravity), momentsOfInertia_(momentsOfInertia) {}

double Object3D::get_mass() const
{
    return mass_;
}//Object3D::get_mass

Vector Object3D::get_center_of_gravity() const
    return centerOfGravity_;
}//Object3D::get_center_of_gravity
{

Vector Object3D::get_moments_of_inertia() const
{
    return momentsOfInertia_;
}//Object3D::get_moment_of_inertia

RectangularCylinder::RectangularCylinder(const double mass, const double xLength, const double yLength, const double zLength, const Vector &centerOfGravity):
    xLength_(xLength), yLength_(yLength), zLength_(zLength)
{
    mass_ = mass, centerOfGravity_ = centerOfGravity;
    update_moment_of_inertia();
    return;
}//RectangularCylinder::RectangularCylinder

void RectangularCylinder::update_moment_of_inertia()
{
    momentsOfInertia_.x = mass_ * (yLength_ * yLength_ + zLength_ * zLength_) / 12.0;
    momentsOfInertia_.y = mass_ * (xLength_ * xLength_ + zLength_ * zLength_) / 12.0;
    momentsOfInertia_.z = mass_ * (xLength_ * xLength_ + yLength_ * yLength_) / 12.0;
    return;
}//RectangularCylinder::update_moment_of_inertia

std::size_t ObjectGroup3D::get_number_of_components() const
{
    return components_.size();
}//ObjectGroup3D::get_number_of_components

double ObjectGroup3D::get_total_mass() const
{
    return totalMass_;
}//ObjectGroup3D::get_total_mass

Vector ObjectGroup3D::get_center_of_gravity() const
{
    return combinedCenterOfGravity_;
}//ObjectGroup3D::get_center_of_gravity

Vector ObjectGroup3D::get_moments_of_inertia() const
{
    return combinedMomentsOfInertia_;
}//ObjectGroup3D::get_moments_of_inertia

Object3D ObjectGroup3D::get_component(int index) const
{
    return components_[index];
}//ObjectGroup3D::get_component

void ObjectGroup3D::add_component(const Object3D &component)
{
    components_.emplace_back(component);
    update_combined_center_of_gravity();
    update_combined_moments_of_inertia();
    return;
}//ObjectGroup3D::add_component

void ObjectGroup3D::update_combined_center_of_gravity()
{
    Vector firstMoment;

    totalMass_ = 0;
    for (Object3D component : components_)
        totalMass_ += component.get_mass();
        
    firstMoment = Vector(0, 0, 0);
    for (Object3D component : components_)
        firstMoment += component.get_mass() * component.get_center_of_gravity();
        
    combinedCenterOfGravity_ = firstMoment / totalMass_;
    
    return;
}//ObjectGroup3D::update_combined_center_of_gravity

void ObjectGroup3D::update_combined_moments_of_inertia()
{
    combinedMomentsOfInertia_ = Vector(0, 0, 0);
    for (Object3D component : components_)
    {
        double xDistance = component.get_center_of_gravity().x - combinedCenterOfGravity_.x;
        double yDistance = component.get_center_of_gravity().y - combinedCenterOfGravity_.y;
        double zDistance = component.get_center_of_gravity().z - combinedCenterOfGravity_.z;

        double xAxisDistanceSquare = yDistance * yDistance + zDistance * zDistance;
        double yAxisDistanceSquare = xDistance * xDistance + zDistance * zDistance;
        double zAxisDistanceSquare = xDistance * xDistance + yDistance * yDistance;

        // The parallel axis theorem
        combinedMomentsOfInertia_ += component.get_moments_of_inertia() + component.get_mass() * Vector(xAxisDistanceSquare, yAxisDistanceSquare, zAxisDistanceSquare);
    }//for component

    return;
}//ObjectGroup3D::update_combined_moments_of_inertia}//ObjectGroup3D::update_combined_moments_of_inertia
/*
Matrix3x3 calculate_inertia_tensor()
{
    constexpr int _NUMELEMENTS = 10;

    double Ixx, Iyy, Izz, Ixy, Ixz, Iyz;

    Ixx = Iyy = Izz = Ixy = Ixz = Iyz = 0;

    PointMass Element[_NUMELEMENTS];
    for (int i = 0; i < _NUMELEMENTS; ++i)
    {
        Ixx += Element[i].LocalInertia.x + 
               Element[i].mass *
               (Element[i].correctedPosition.y * Element[i].correctedPosition.y +
               Element[i].correctedPosition.z * Element[i].correctedPosition.z);
        
        Iyy += Element[i].LocalInertia.y + 
               Element[i].mass *
               (Element[i].correctedPosition.x * Element[i].correctedPosition.x +
               Element[i].correctedPosition.z * Element[i].correctedPosition.z);
        
        Izz += Element[i].LocalInertia.z + 
               Element[i].mass *
               (Element[i].correctedPosition.x * Element[i].correctedPosition.x +
               Element[i].correctedPosition.y * Element[i].correctedPosition.y);

        Ixy += Element[i].mass *
               (Element[i].correctedPosition.x * Element[i].correctedPosition.y);

        Ixz += Element[i].mass *
               (Element[i].correctedPosition.x * Element[i].correctedPosition.z);

        Iyz += Element[i].mass *
               (Element[i].correctedPosition.y * Element[i].correctedPosition.z);
    }//for i

    Matrix3x3 InertiaTensor;

    InertiaTensor.e11 =  Ixx, InertiaTensor.e12 = -Ixy, InertiaTensor.e13 = -Ixz;
    InertiaTensor.e21 = -Ixy, InertiaTensor.e22 =  Iyy, InertiaTensor.e23 = -Iyz;
    InertiaTensor.e31 = -Ixz, InertiaTensor.e32 = -Iyz, InertiaTensor.e33 =  Izz;

    return InertiaTensor;
}//calculate_inertia_tensor
*/