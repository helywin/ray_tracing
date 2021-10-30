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

    bool front_face;

    inline void set_face_normal(const ray &r, const vec3 &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
public:
    // 根据光线距离计算是否命中
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};

#endif //RAY_TRACING_HITTABLE_HPP
