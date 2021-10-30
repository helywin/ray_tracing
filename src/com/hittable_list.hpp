//
// Created by helywin on 2021/10/29.
//

#ifndef RAY_TRACING_HITTABLE_LIST_HPP
#define RAY_TRACING_HITTABLE_LIST_HPP

#include "hittable.hpp"
#include "constants.hpp"

#include <vector>

class hittable_list : public hittable
{
public:
    hittable_list() = default;
    hittable_list(std::initializer_list<shared_ptr<hittable>> args)
    {
        for (const auto &e: args) {
            objects.push_back(e);
        }
    }

    void clear()
    { objects.clear(); }

    void add(const shared_ptr<hittable> &object)
    { objects.push_back(object); }

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

public:
    std::vector<std::shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object: objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif //RAY_TRACING_HITTABLE_LIST_HPP
