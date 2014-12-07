// Exercise 12: A Ray Tracer!
// Test program for sub task d): "Rasterization"
//
// Version 2, changes:
// 04.12.2014 Additionally accept rays starting at camera location
//            Rays starting at pixel plane are ofcourse still accepted.

#include <iostream>
#include <cmath>
#include "raytracer.cpp"

namespace raytracer_test
{
    const double eps = 0.0001;

    bool report(std::string name, bool result)
    {
        std::cout << "test " << name;
            if (result)
            std::cout << " passed.\n";
        else
            std::cout << " failed.\n";
        return result;
    }

    bool is_equal(double d1, double d2)
    {
        return fabs(d1 - d2) <= ((fabs(d1) > fabs(d2) ? fabs(d2) : fabs(d1)) * eps);
    }

    bool is_equal(Vector v1, Vector v2)
    {
        return is_equal(v1.x, v2.x) && is_equal(v1.y, v2.y) && is_equal(v1.z, v2.z);
    }

    bool is_equal(Ray ray1, Ray ray2)
    {
        return is_equal(ray1.start, ray2.start) && is_equal(ray1.direction, ray2.direction);
    }

    bool test_rasterization()
    {
        bool result = true;

        Scene scene(Vector(0, 0, -1), Vector(0, 0, 0), White, 4, 4);

        Ray ray1_res = scene.create_ray(0, 0);
        Ray ray1_expect_a = Ray(Vector(-0.375, 0.375, 0.0),  Vector(-0.375, 0.375, 1));
        Ray ray1_expect_b = Ray(Vector(0, 0, -1),            Vector(-0.375, 0.375, 1));
        result &= report("ray 1",is_equal(ray1_res, ray1_expect_a) || is_equal(ray1_res, ray1_expect_b));

        Ray ray2_res = scene.create_ray(0, 3);
        Ray ray2_expect_a = Ray(Vector(-0.375,-0.375, 0.0), Vector(-0.375, -0.375, 1));
        Ray ray2_expect_b = Ray(Vector(0, 0, -1),           Vector(-0.375, -0.375, 1));
        result &= report("ray 2",is_equal(ray2_res, ray2_expect_a) || is_equal(ray2_res, ray2_expect_b));

        Ray ray3_res = scene.create_ray(3, 0);
        Ray ray3_expect_a = Ray(Vector(0.375, 0.375, 0.0),  Vector(0.375, 0.375, 1));
        Ray ray3_expect_b = Ray(Vector(0, 0, -1),           Vector(0.375, 0.375, 1));
        result &= report("ray 3",is_equal(ray3_res, ray3_expect_a) || is_equal(ray3_res, ray3_expect_b));

        Ray ray4_res = scene.create_ray(3, 3);
        Ray ray4_expect_a = Ray(Vector(0.375,-0.375, 0.0), Vector(0.375, -0.375, 1));
        Ray ray4_expect_b = Ray(Vector(0, 0, -1),          Vector(0.375, -0.375, 1));
        result &= report("ray 4",is_equal(ray4_res, ray4_expect_a) || is_equal(ray4_res, ray4_expect_b));

        return result;
    }
} // namespace raytracer_test

int main()
{
    bool result = true;
    result &= raytracer_test::test_rasterization();
    raytracer_test::report("raytracer sub task d", result);
}
