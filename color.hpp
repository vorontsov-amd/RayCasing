#include "vector.hpp"

class Color : public Vector
{
public:
    explicit Color(double R = 0, double G = 0, double B = 0) : Vector(R, G, B) {}
    Color(const Vector vec) : Vector(vec) {}

    Color& operator*=(const Color& right)
    {
        double R = getX();
        double G = getX();
        double B = getX();

        R *= right.getX();
        G *= right.getY();
        B *= right.getZ();

        R /= 255;
        G /= 255;
        B /= 255;

        setX(R);
        setY(G);
        setZ(B);

        return *this;
    }

    Color operator*(const Color& right)
    {
        Color result = *this;
        result *= right;
        return result;
    }

    /*Color& operator*=(double num)
    {
        double R = getX();
        double G = getX();
        double B = getX();

        R *= num;
        G *= num;
        B *= num;

        if (R >= 255) R = 255;
        if (G >= 255) G = 255;
        if (B >= 255) B = 255;

        setX(R);
        setY(G);
        setZ(B);

        return *this;
    }

    Color operator*(double num)
    {
        Color result = *this;
        result *= num;
        return result;
    }*/
};
