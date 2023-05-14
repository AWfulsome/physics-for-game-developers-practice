#include "PhysicsObject.hpp"
#include "Vector.hpp"

PointMass::PointMass(const double mass_, const Vector &dP_, const Vector &cP_):
    mass(mass_), designPosition(dP_), correctedPosition(cP_) {}

Object3D::Object3D(const double mass, const Vector &centerOfMass, const Vector &momentsOfInertia):
    mass_(mass), centerOfMass_(centerOfMass), momentsOfInertia_(momentsOfInertia) {}

double Object3D::get_mass() const
{
    return mass_;
}//Object3D::get_mass

Vector Object3D::get_center_of_mass() const
{
    return centerOfMass_;
}//Object3D::get_CG()

Vector Object3D::get_moments_of_inertia() const
{
    return momentsOfInertia_;
}//Object3D::get_moment_of_inertia

RectangularCylinder::RectangularCylinder(const double mass, const double xLength, const double yLength, const double zLength, const Vector &centerOfMass):
    xLength_(xLength), yLength_(yLength), zLength_(zLength)
{
    mass_ = mass, centerOfMass_ = centerOfMass;
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

Vector ObjectGroup3D::get_center_of_mass() const
{
    return combinedCenterOfMass_;
}//ObjectGroup3D::get_center_of_mass

Vector ObjectGroup3D::get_moments_of_inertia() const
{
    return combinedMomentsOfInertia_;
}//ObjectGroup3D::get_moments_of_inertia

Object3D ObjectGroup3D::get_component(int index) const
{
    return components_[index];
}//ObjectGroup3D::get_component

void ObjectGroup3D::add_component(Object3D component)
{
    components_.emplace_back(component);
    update_combined_center_of_mass();
    update_combined_moments_of_inertia();
    return;
}//ObjectGroup3D::add_component

void ObjectGroup3D::update_combined_center_of_mass()
{
    Vector firstMoment;

    totalMass_ = 0;
    for (Object3D component : components_)
        totalMass_ += component.get_mass();
        
    firstMoment = Vector(0, 0, 0);
    for (Object3D component : components_)
        firstMoment += component.get_mass() * component.get_center_of_mass();
        
    combinedCenterOfMass_ = firstMoment / totalMass_;
    
    return;
}//ObjectGroup3D::update_combined_center_of_mass

void ObjectGroup3D::update_combined_moments_of_inertia()
{
    combinedMomentsOfInertia_ = Vector(0, 0, 0);
    for (Object3D component : components_)
    {
        double xDistance = component.get_center_of_mass().x - combinedCenterOfMass_.x;
        double yDistance = component.get_center_of_mass().y - combinedCenterOfMass_.y;
        double zDistance = component.get_center_of_mass().z - combinedCenterOfMass_.z;

        double xAxisDistanceSquare = yDistance * yDistance + zDistance * zDistance;
        double yAxisDistanceSquare = xDistance * xDistance + zDistance * zDistance;
        double zAxisDistanceSquare = xDistance * xDistance + yDistance * yDistance;

        // The parallel axis theorem
        combinedMomentsOfInertia_ += component.get_moments_of_inertia() + component.get_mass() * Vector(xAxisDistanceSquare, yAxisDistanceSquare, zAxisDistanceSquare);
    }//for component

    return;
}//ObjectGroup3D::update_combined_moments_of_inertia