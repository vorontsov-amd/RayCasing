#include <iostream>
#include "vector.hpp"
#include "sphere.hpp"

auto CreateSysCoord(unsigned x, unsigned y)
{
    Vector i = {1, 0, 0}, j = {0, -1, 0}, k = {0, 0, 1};
    Vector O  = {static_cast<double> (x) / 2, 
                static_cast<double> (y) / 2};
    return SystemCoord(O, i, j, k);
}

auto square(double x) { return x * x; }

void RenderCircle(sf::RenderWindow& window, const SystemCoord& system)
{
    sf::RectangleShape pixel(sf::Vector2f(1, 1));
    Sphere sphere(100, system.cstart_point);

    Vector radius_point = {};

    for (int y = 0, height = window.getSize().y; y < height; ++y)
    {
        for (int x = 0, weight = window.getSize().x; x < weight; ++x)
        {
            pixel.setPosition(x, y);
            radius_point = system.recalcCoord(x, y);

            std::cout << radius_point << '\n';

            if (sphere.сontainsInside(radius_point))
            {
                pixel.setFillColor(sf::Color(sphere.ccolor.getX(), sphere.ccolor.getY(), sphere.ccolor.getZ()));
                window.draw(pixel);
            }
            else
            {
                pixel.setFillColor(sf::Color::Black);
                window.draw(pixel);
            }
        }
    }
}

int main()
{   
    const int X = 400, Y = 400;

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