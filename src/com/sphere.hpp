//
// Created by jiang on 2021/10/29.
//

#ifndef RAY_TRACING_SPHERE_HPP
#define RAY_TRACING_SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable
{
public:
    sphere() = default;

    sphere(const point3 &cen, double r) : center(cen), radius(r)
    {};

    

public:
    point3 center;
    double radius;
};

#endif //RAY_TRACING_SPHERE_HPP
