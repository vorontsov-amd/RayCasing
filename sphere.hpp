#include <iostream>
#include <cmath>
#include "vector.hpp"
#include "double.hpp"

class Sphere
{
public:
    double cradius;
    Vector ccenter;
    Vector ccolor;
public:
    Sphere(double radius, const Vector& center, const Vector& color = Vector(0, 200, 100)) :
        cradius(radius),
        ccenter(center),
        ccolor(color)
        {} 

    bool сontains(const Vector& point) const; 
    bool сontainsInside(const Vector& point) const; 
    Vector normal(const Vector& point) const;  

};

inline bool Sphere::сontains(const Vector& point) const
{    
    Double x  =   point.getX(), y  =   point.getY(),  z =   point.getZ(), radius = cradius,
           x0 = ccenter.getX(), y0 = ccenter.getY(), z0 = ccenter.getZ();

    return (x - x0 ^ 2) + (y - y0 ^ 2) + (z - z0 ^ 2) == (radius ^ 2);  
}

inline bool Sphere::сontainsInside(const Vector& point) const
{    
    Double x  =   point.getX(), y  =   point.getY(),  z =   point.getZ(), radius = cradius,
           x0 = ccenter.getX(), y0 = ccenter.getY(), z0 = ccenter.getZ();


    Double l = (x - x0 ^ 2) + (y - y0 ^ 2) + (z - z0 ^ 2) ;
    Double R = radius ^ 2;
    auto st =  (x - x0 ^ 2) + (y - y0 ^ 2) + (z - z0 ^ 2) <= (radius ^ 2);  
    std::cout << std::boolalpha << l << " " << R << '\n';
    return st;
}

inline Vector Sphere::normal(const Vector& point) const
{
    if (!сontains(point))
    {
        return Vector(0, 0, 0);
    }

    return Vector(point.getX() - ccenter.getX(), point.getY() - ccenter.getY(), point.getZ() - ccenter.getZ());
}
