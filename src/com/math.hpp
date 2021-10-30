//
// Created by helywin on 2021/10/30.
//

#ifndef RAY_TRACING_RANDOM_HPP
#define RAY_TRACING_RANDOM_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <random>

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

#endif //RAY_TRACING_RANDOM_HPP
