#include <iostream>

#include "PhysicsObject.hpp"
#include "Vector.hpp"

// This is the revised version of 00-SimpleStaticCar, mainly focused on PhysicsObject.
// - PointMass is now derived from Object3D.
// - Replaced moments of inertia vector with inertia tensor matrix.
// - Added inertia tensor related methods.
// - Added corrected center of gravity and corrected inertia tensor.
//   Both are relative to the combined ones.

RectangularCylinder cin_rectangular_cylinder(const std::string name)
{
    float mass, xLength, yLength, zLength, x, y, z;
    
    std::cout << name << " mass (kg) ...> ";
    std::cin >> mass;

    std::cout << name << " x-length (m) ...> ";
    std::cin >> xLength;
    
    std::cout << name << " y-length (m) ...> ";
    std::cin >> yLength;
    
    std::cout << name << " z-length (m) ...> ";
    std::cin >> zLength;
    
    std::cout << name << " x centroid coordinate (m) ...> ";
    std::cin >> x;
    
    std::cout << name << " y centroid coordinate (m) ...> ";
    std::cin >> y;
    
    std::cout << name << " z centroid coordinate (m) ...> ";
    std::cin >> z;

    return RectangularCylinder(mass, xLength, yLength, zLength, Vector(x, y, z));
}//get_rectangular_cylinder

int main()
{
    RectangularCylinder carBody = cin_rectangular_cylinder("car body");
    RectangularCylinder driver = cin_rectangular_cylinder("driver");
    RectangularCylinder fuelTank = cin_rectangular_cylinder("fuel tank");
    
    ObjectGroup3D car;

    car.add_component(carBody);
    car.add_component(driver);
    car.add_component(fuelTank);

    std::cout << "Combined mass: " << car.get_total_mass() << " kg\n"
              << "Combined center of mass: " << car.get_center_of_gravity() << '\n'
              << "Combined moments of inertia: " << car.get_moments_of_inertia() << std::endl;

    return 0;
}//main