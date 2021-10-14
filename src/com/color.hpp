//
// Created by helywin on 2021/10/14.
//

#ifndef RAY_TRACING_COLOR_HPP
#define RAY_TRACING_COLOR_HPP

#include "vec3.hpp"

#include <iostream>

void write_color(std::ostream &out, const color &pixel_color)
{
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif //RAY_TRACING_COLOR_HPP