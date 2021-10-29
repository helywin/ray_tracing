//
// Created by jiang on 2021/10/29.
//

#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <iostream>
#include <fstream>

const point3 SPHERE_CENTER{0, 0, -1};

double hit_sphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

color ray_color(const ray &r)
{
    auto t = hit_sphere(SPHERE_CENTER, 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - SPHERE_CENTER);
        return 0.5 * (color(N + 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
// Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // 相机投影面

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;    // 焦距

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render
    std::ofstream fs("normal.ppm", std::ios_base::trunc);
    fs << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            // 从相机位置发射到投影面的光线
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            write_color(fs, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}