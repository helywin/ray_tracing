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

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;


public:
    point3 center;
    double radius{};
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return false;
    }
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max) {
            return false;
        }
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    return true;
}

#endif //RAY_TRACING_SPHERE_HPP
