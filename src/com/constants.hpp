//
// Created by helywin on 2021/10/29.
//

#ifndef RAY_TRACING_CONSTANTS_HPP
#define RAY_TRACING_CONSTANTS_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <random>

#include "ray.hpp"
#include "vec3.hpp"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

constexpr inline double degree_to_radians(double degree)
{
    return degree * pi / 180.0;
}

inline double random_double()
{
    static std::mt19937 generator;
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double random_double(double min, double max)
{
    static std::mt19937 generator;
    static std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

inline constexpr double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif //RAY_TRACING_CONSTANTS_HPP
