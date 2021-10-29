//
// Created by jiang on 2021/10/29.
//

#ifndef RAY_TRACING_HITTABLE_HPP
#define RAY_TRACING_HITTABLE_HPP

#include "ray.hpp"

struct hit_record
{
    point3 p;
    vec3 normal;
    double t;     // 距离
};

class hittable
{
public:
    // 根据光线距离计算是否命中
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) = 0;
};

#endif //RAY_TRACING_HITTABLE_HPP
