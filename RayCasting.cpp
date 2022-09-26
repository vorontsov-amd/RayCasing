#include <iostream>
#include "vector.hpp"
#include "sphere.hpp"
#include "color.hpp"

auto CreateSysCoord(unsigned x, unsigned y)
{
    Vector i = {1, 0, 0}, j = {0, -1, 0}, k = {0, 0, 1};
    Vector O  = {static_cast<double> (x) / 2, 
                 static_cast<double> (y) / 2};
    return SystemCoord(O, i, j, k);
}

void RenderCircle(sf::RenderWindow& window, const SystemCoord& system)
{
    Sphere sphere(300, system.cstart_point);

    sf::RectangleShape pixel(sf::Vector2f(1, 1));

    Vector radius_point = {};

    Vector LigthSource(-200, 300, 700, system);
    Color  SourceColor(255, 250, 250);
    Color  SphereColor(sphere.ccolor);

    for (int y = 0, height = window.getSize().y; y < height; ++y)
    {
        for (int x = 0, weight = window.getSize().x; x < weight; ++x)
        {
            pixel.setPosition(x, y);

            radius_point = system.recalcCoord(x, y);

            if (sphere.сontainsInside(Vector(x, y)))
            {                
                double z = std::sqrt((Double(sphere.cradius) ^ 2) - 
                                     (Double(x - sphere.ccenter.getX()) ^ 2) -
                                     (Double(y - sphere.ccenter.getY()) ^ 2)) +
                           sphere.ccenter.getZ();
                
                Vector L = LigthSource - Vector(x, y, z);
                Vector n = sphere.normal(Vector(x, y, z));

                double D = cos(L, n); 
                D = (D < 0) ? 0 : D;

                Vector V = Vector(0, 0, 1000, system) - Vector(x, y, z);
                Vector reflected = n * (2 * (n * L) / (n.length() * n.length())) - L;

                double S = Double(0.93) * Double(cos(V, reflected)) ^ 30;
                S = (S < 0) ? 0 : S;

                double A = 0.06;

                Color PointColor = static_cast<Vector> (SourceColor * SphereColor) * D +  
                                   static_cast<Vector> (SourceColor * SphereColor) * A +
                                   static_cast<Vector> (SourceColor) * S; 



                pixel.setFillColor(sf::Color(PointColor.getX(), PointColor.getY(), PointColor.getZ()));
                window.draw(pixel);
            }
            else
            {
                pixel.setFillColor(sf::Color(100, 100, 100));
                window.draw(pixel);
            }
        }
    }
}

int main()
{   
    const int X = 800, Y = 800;

    sf::RenderWindow window(sf::VideoMode(X, Y), "RayCasting");
    auto system = CreateSysCoord(X, Y); 
    
    while (window.isOpen())
    {
        window.clear(sf::Color(120, 120, 120));

        sf::Event event;
        while (window.pollEvent(event))
        {            
            if (event.type == sf::Event::Closed)
                window.close();
        }

        RenderCircle(window, system);
        
        window.display();
    }
}