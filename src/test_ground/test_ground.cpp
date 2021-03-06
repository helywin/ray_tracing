//
// Created by jiang on 2021/10/29.
//

#include "constants.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include <iostream>
#include <fstream>

color ray_color(const ray &r, const hittable &world)
{
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        // 法向量转rgb数据的公式
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    // 未被击中显示天空背景色
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(int argc, char *argv[])
{
// 图片大小
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1024;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // 世界物体
    hittable_list world{
            make_shared<sphere>(point3(0, 0, -1), -.5),
            make_shared<sphere>(point3(0, -100.5, -1), 100)
    };

    // 相机投影面
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;    // 焦距

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render
    auto full_path = std::string(argv[0]);
    auto splash_pos = full_path.find_last_of('\\');
    auto dot_pos = full_path.find_last_of('.');
    auto name = full_path.substr(splash_pos + 1, dot_pos - splash_pos - 1) + ".ppm";
    std::ofstream fs(name, std::ios_base::trunc);
    fs << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
//        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            // 从相机位置发射到投影面的光线
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r, world);
            write_color(fs, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}