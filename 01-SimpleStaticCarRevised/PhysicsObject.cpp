#include "PhysicsObject.hpp"
#include "Vector.hpp"

Object3D::Object3D(const double mass, const Vector &centerOfGravity, const Matrix3x3 &inertiaTensor):
    mass_(mass), centerOfGravity_(centerOfGravity), inertiaTensor_(inertiaTensor) {}

double Object3D::get_mass() const
{
    return mass_;
}//Object3D::get_mass

Vector Object3D::get_center_of_gravity() const
{
    return centerOfGravity_;
}//Object3D::get_center_of_gravity

Vector Object3D::get_corrected_center_of_gravity() const
{
    return correctedCenterOfGravity_;
}//Object3D::get_corrected_center_of_gravity

Vector Object3D::get_moments_of_inertia() const
{
    return Vector(inertiaTensor_.e11, inertiaTensor_.e22, inertiaTensor_.e33);
}//Object3D::get_moment_of_inertia

Vector Object3D::get_corrected_moments_of_inertia() const
{
    return Vector(correctedInertiaTensor_.e11, correctedInertiaTensor_.e22, correctedInertiaTensor_.e33);
}//Object3D::get_corrected_moment_of_inertia

Matrix3x3 Object3D::get_inertia_tensor() const
{
    return inertiaTensor_;
}//Object3D::get_inertia_tensor

Matrix3x3 Object3D::get_corrected_inertia_tensor() const
{
    return correctedInertiaTensor_;
}//Object3D::get_corrected_inertia_tensor

void Object3D::update_corrected_center_of_gravity(const Vector &combinedCenterOfGravity)
{
    correctedCenterOfGravity_ = centerOfGravity_ - combinedCenterOfGravity;
    return;
}//Object3D::update_corrected_center_of_gravity

void Object3D::update_corrected_inertia_tensor(const Vector &combinedCenterOfGravity)
{
    double Ixx, Iyy, Izz, Ixy, Ixz, Iyz;

    Ixx = inertiaTensor_.e11 + 
          mass_ * (correctedCenterOfGravity_.y * correctedCenterOfGravity_.y +
                   correctedCenterOfGravity_.z * correctedCenterOfGravity_.z);
        
    Iyy = inertiaTensor_.e22 + 
          mass_ * (correctedCenterOfGravity_.x * correctedCenterOfGravity_.x +
                   correctedCenterOfGravity_.z * correctedCenterOfGravity_.z);
    
    Izz = inertiaTensor_.e33 + 
          mass_ * (correctedCenterOfGravity_.x * correctedCenterOfGravity_.x +
                  correctedCenterOfGravity_.y * correctedCenterOfGravity_.y);

    Ixy = mass_ * (correctedCenterOfGravity_.x * correctedCenterOfGravity_.y);
    Ixz = mass_ * (correctedCenterOfGravity_.x * correctedCenterOfGravity_.z);
    Iyz = mass_ * (correctedCenterOfGravity_.y * correctedCenterOfGravity_.z);

    correctedInertiaTensor_ = Matrix3x3( Ixx, -Ixy, -Ixz,
                                        -Ixy,  Iyy, -Iyz,
                                        -Ixz, -Iyz,  Izz);

    return;
}//Object3D::update_corrected_moments_of_inertia

PointMass::PointMass(const double mass, const Vector &centerOfGravity)
{
    mass_ = mass;
    centerOfGravity_ = correctedCenterOfGravity_ = centerOfGravity;
    inertiaTensor_ = correctedInertiaTensor_ = Matrix3x3::ZERO;
    return;
}//PointMass::PointMass

RectangularCylinder::RectangularCylinder(const double mass, const double xLength, const double yLength, const double zLength, const Vector &centerOfGravity):
    xLength_(xLength), yLength_(yLength), zLength_(zLength)
{
    mass_ = mass;
    centerOfGravity_ = correctedCenterOfGravity_ = centerOfGravity;

    double momentOfInertiaX = mass_ * (yLength_ * yLength_ + zLength_ * zLength_) / 12.0;
    double momentOfInertiaY = mass_ * (xLength_ * xLength_ + zLength_ * zLength_) / 12.0;
    double momentOfInertiaZ = mass_ * (xLength_ * xLength_ + yLength_ * yLength_) / 12.0;
    
    inertiaTensor_ = correctedInertiaTensor_ = Matrix3x3(momentOfInertiaX, 0, 0,
                                                         0, momentOfInertiaY, 0,
                                                         0, 0, momentOfInertiaZ);

    return;
}//RectangularCylinder::RectangularCylinder

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
    return Vector(combinedInertiaTensor_.e11, combinedInertiaTensor_.e22, combinedInertiaTensor_.e33);
}//ObjectGroup3D::get_moments_of_inertia

Object3D ObjectGroup3D::get_component(int index) const
{
    return components_[index];
}//ObjectGroup3D::get_component

void ObjectGroup3D::add_component(const Object3D &component)
{
    components_.emplace_back(component);
    update_combined_center_of_gravity();
    update_combined_inertia_tensor();
    return;
}//ObjectGroup3D::add_component

void ObjectGroup3D::update_combined_center_of_gravity()
{
    Vector firstMoment;

    totalMass_ = 0;
    for (const Object3D &component : components_)
        totalMass_ += component.get_mass();
        
    firstMoment = Vector(0, 0, 0);
    for (const Object3D &component : components_)
        firstMoment += component.get_mass() * component.get_center_of_gravity();
        
    combinedCenterOfGravity_ = firstMoment / totalMass_;

    for (Object3D &component : components_)
        component.update_corrected_center_of_gravity(combinedCenterOfGravity_);
    
    return;
}//ObjectGroup3D::update_combined_center_of_gravity

void ObjectGroup3D::update_combined_inertia_tensor()
{
    combinedInertiaTensor_ = Matrix3x3::ZERO;

    for (Object3D &component : components_)
    {
        component.update_corrected_inertia_tensor(combinedCenterOfGravity_);
        combinedInertiaTensor_ += component.get_corrected_inertia_tensor();
    }//for component

    return;
}//ObjectGroup3D::update_combined_moments_of_inertia

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