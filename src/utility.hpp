#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace my {

const double PI = 3.14159265;
// const float PIXEL_PER_METER = 3779.52;
const float PIXEL_PER_METER = 377.952;

/**
 * Returns the angle from horizontal b/w 0 and 180 degrees.
 * Anti-Clockwise (up) from horizontal is +ve.
 * Clockwise (down) from horizontal is -ve.
 */
inline double angle(sf::Vector2f v)
{
    return atan2(v.y, v.x) * 180.0 / PI;
}

inline double area(double radius)
{
    return PI * radius * radius;
}

inline double dot(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

inline double distance(sf::Vector2f a, sf::Vector2f b)
{
    double x = (a.x - b.x) * (a.x - b.x);
    double y = (a.y - b.y) * (a.y - b.y);
    return (double)sqrt(x + y);
}

inline sf::Vector2f closest_point_on_line(sf::Vector2f point, std::pair<sf::Vector2f, sf::Vector2f> segment)
{
    sf::Vector2f f_2_s(segment.second.x - segment.first.x, segment.second.y - segment.first.y);
    sf::Vector2f f_2_p(point.x - segment.first.x, point.y - segment.first.y);

    double t = dot(f_2_p, f_2_s) / dot(f_2_s, f_2_s);
    if (t < 0)
        t = 0;
    if (t > 1)
        t = 1;

    return segment.first + sf::Vector2f(f_2_s.x * t, f_2_s.y * t);
}

inline double distance(sf::Vector2f point, std::pair<sf::Vector2f, sf::Vector2f> segment)
{
    return distance(point, closest_point_on_line(point, segment));
}

inline sf::Vector2f vector_by_mag_angle(double mag, double deg)
{
    double radians = deg * M_PI / 180.0;
    return { mag * cos(radians), mag * sin(radians) };
}

inline double vector_mag(sf::Vector2f v)
{
    return sqrt((v.x * v.x) + (v.y * v.y));
}

inline double angle_between(sf::Vector2f a, sf::Vector2f b)
{
    return acos(dot(a, b) / (vector_mag(a) * vector_mag(b))) * 180.0 / PI;
}

}

#endif