//
// Created by helywin on 2021/10/14.
//

#ifndef RAY_TRACING_COLOR_HPP
#define RAY_TRACING_COLOR_HPP

#include "vec3.hpp"
#include "math.hpp"

#include <iostream>

void write_color(std::ostream &out, const color &pixel_color)
{
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

void write_color(std::ostream &out, const color &pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

void write_color(const color &pixel_color, int samples_per_pixel, unsigned char *p)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    p[0] = static_cast<unsigned char>(256 * clamp(r, 0.0, 0.999));
    p[1] = static_cast<unsigned char>(256 * clamp(g, 0.0, 0.999));
    p[2] = static_cast<unsigned char>(256 * clamp(b, 0.0, 0.999));
}

#endif //RAY_TRACING_COLOR_HPP
