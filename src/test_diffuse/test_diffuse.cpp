//
// Created by jiang on 2021/10/29.
//

#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#include <iostream>
#include <fstream>
#include <mutex>
#ifdef _WINDOWS
#include <omp.h>
#endif

// 利用递归把光路逆转
color ray_color(const ray &r, const hittable &world, int depth)
{
    hit_record rec;
    // 反射次数
    if (depth <= 0) {
        return {0, 0, 0};
    }
    // 设置0.001阻止不断重复反射
    if (world.hit(r, 0.001, infinity, rec)) {
        // 产生随机漫反射
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        // 子光线
        return 0.5 * ray_color({rec.p, target - rec.p}, world, depth - 1);
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
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    const int pixels = image_width * image_height;

    std::vector<unsigned char> data(pixels * 3);

    // 世界物体
    hittable_list world{
            std::make_shared<sphere>(point3(0, 0, -1), -.5),
            std::make_shared<sphere>(point3(0, -100.5, -1), 100)
    };

    // 相机投影面
    camera cam;

    // Render
    auto full_path = std::string(argv[0]);
#ifdef _WINDOWS
    auto splash_pos = full_path.find_last_of('\\');
#else
    auto splash_pos = full_path.find_last_of('/');
#endif
    auto dot_pos = full_path.find_last_of('.');
    auto name = full_path.substr(splash_pos + 1, dot_pos - splash_pos - 1) + ".png";

    std::mutex lock;
    int count = 0;

#pragma omp  for
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            color pixel_color{0, 0, 0};
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            int index = ((image_height - 1 - j) * image_width + i) * 3;
            write_color(pixel_color, samples_per_pixel, data.data() + index);
        }
        lock.lock();
        count += 1;
        std::cout << "progress: " << count / (double) image_height * 100 << "%.\r";
        std::cout.flush();
        lock.unlock();
    }

    stbi_write_png(name.c_str(), image_width, image_height, 3, data.data(), image_width * 3);

    std::cerr << "\nDone.\n";
}
