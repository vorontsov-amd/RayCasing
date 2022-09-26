#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

struct SystemCoord;

struct Point
{
    double cx;
    double cy;
    double cz;

    Point(double x = 0, double y = 0, double z = 0) : cx(x), cy(y), cz(z) {}
};

class Vector
{
public:
    enum Thickness { thin, medium, bold };
private:
    double cx;
    double cy;
    double cz;
    double clen;

    Point capp_point       = Point(0, 0, 0);
    sf::VertexArray cline  = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray carrow = sf::VertexArray(sf::LineStrip, 3);
    Thickness cthickness   = Thickness::thin;

    void fillVertexArray();
    void createLine();
    void createArrow();
    void moveFigure(int x, int y);
public:
    Vector(double x = 0, double y = 0, double z = 0) : cx(x),       cy(y),       cz(z),         clen(NAN) {}
    Vector(const Vector& init)                       : cx(init.cx), cy(init.cy), cz(init.cz),   clen(init.clen) {}
    Vector(double x, double y, double z, const SystemCoord& sys);

    double length();

    void setThickness(Thickness thickness) { cthickness = thickness; }
    void setAppPoint(const Point& app_point, const SystemCoord& sys_coord);
    void setAppPoint(const Point& app_point);
    void setColor(const sf::Color& color);

    void setX(double x) { cx = x; clen = NAN; }
    void setY(double y) { cy = y; clen = NAN; }
    void setZ(double z) { cz = z; clen = NAN; }

    void setX(double x, const SystemCoord& sys_coord);
    void setY(double y, const SystemCoord& sys_coord);
    void setZ(double z, const SystemCoord& sys_coord);

    double getX() const { return cx; }
    double getY() const { return cy; }
    double getZ() const { return cz; }

    Vector& operator+=(const Vector& rvec);
    Vector& operator-=(const Vector& rvec);
    Vector& operator/=(double number);
    Vector& operator*=(double number);

    Vector operator+(const Vector& rvec) const;
    Vector operator-(const Vector& rvec) const;
    Vector operator/(double number) const;
    Vector operator*(double number) const;

    int operator*(const Vector& rvec) const { return cx * rvec.cx + cy * rvec.cy + cz * rvec.cz; }

    Vector operator-() const { return Vector(-cx, -cy, -cz); }

    Vector normalize() { return Vector(cx / length(), cy / length(), cz / length()); }

    void draw(sf::RenderWindow& window);

    friend double cos(Vector& left, Vector& right) { return left * right / (left.length() * right.length()); }

    friend std::ostream& operator<<(std::ostream& out, const Vector& vec);
    friend std::istream& operator>>(std::istream& in, Vector& vec);
};

struct SystemCoord
{
    Vector cstart_point;
    Vector ce1;
    Vector ce2;
    Vector ce3;

    SystemCoord(const Vector& start_point, const Vector& e1, const Vector& e2, const Vector& e3) :
        cstart_point(start_point),
        ce1(e1),
        ce2(e2),
        ce3(e3)
        {}

    Vector recalcCoord(double x, double y, double z = 0) const
    {
        const static double determinate = ce1.getX() * ce3.getY() * ce2.getZ() -
                                          ce1.getX() * ce3.getZ() * ce2.getY() +
                                          ce1.getY() * ce3.getZ() * ce2.getX() -
                                          ce1.getY() * ce3.getX() * ce2.getZ() -
                                          ce1.getZ() * ce3.getY() * ce2.getX() +
                                          ce1.getZ() * ce3.getX() * ce3.getY();

        const static Vector e1 = { ce3.getY() * ce2.getZ() - ce3.getZ() * ce2.getY(),
                                   ce1.getY() * ce3.getZ() - ce1.getZ() * ce3.getY(),
                                   ce2.getY() * ce1.getZ() - ce2.getZ() * ce1.getY() };

        const static Vector e2 = { ce3.getZ() * ce2.getX() - ce3.getX() * ce2.getZ(),
                                   ce1.getZ() * ce3.getX() - ce1.getX() * ce3.getZ(),
                                   ce2.getZ() * ce1.getX() - ce2.getX() * ce1.getZ() };

        const static Vector e3 = { ce3.getX() * ce2.getY() - ce3.getY() * ce2.getX(),
                                   ce1.getX() * ce3.getY() - ce1.getY() * ce3.getX(), 
                                   ce2.getX() * ce1.getY() - ce2.getY() * ce1.getX() };

        const static Vector entry = { e1.getX() * cstart_point.getX() + e2.getX() * cstart_point.getY() + e3.getX() * cstart_point.getZ(),
                                      e1.getY() * cstart_point.getX() + e2.getY() * cstart_point.getY() + e3.getY() * cstart_point.getZ(),
                                      e1.getZ() * cstart_point.getX() + e2.getZ() * cstart_point.getY() + e3.getZ() * cstart_point.getZ() };

        Vector result = { e1.getX() * x + e2.getX() * y + e3.getX() * z,
                          e1.getY() * x + e2.getY() * y + e3.getY() * z,
                          e1.getZ() * x + e2.getZ() * y + e3.getZ() * z };

        result /= determinate;
        result -= entry;

        return result;
    }
};
