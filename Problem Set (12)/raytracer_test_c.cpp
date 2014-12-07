// Exercise 12: A Ray Tracer!
// Test program for sub task c: "Intersect with nearest object"

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

    bool test_intersect(const Scene& scene, const Ray& ray, bool intersects_expect, double t_expect)
    {
        double t_res;
        bool intersects_res = scene.intersect(ray, t_res) != NULL;
        return intersects_res == intersects_expect && (!intersects_res || is_equal(t_res, t_expect));
    }

    bool test_intersect_scene()
    {
        bool result = true;

        Shape sphere_small(0, Vector(3, 3, 3), 1, White, White, White);
        Shape sphere_big (0, Vector(3, 6, 3), 2,  White, White, White);
        Shape plane(1, Vector(0, 1, 0), 6,        White, White, White);

        Scene scene(Vector(0, 0, -1), Vector(0, 0, 0), White, 4, 4);
        scene.add_shape(sphere_big);
        scene.add_shape(sphere_small);
        scene.add_shape(plane);

        result &= report("scene 1",test_intersect(scene, Ray(Vector(0, 0, 0),     Vector(0, 1, 0)),       true,   6));
        result &= report("scene 2",test_intersect(scene, Ray(Vector(1, 1, 2),     Vector(2, 2, 1)),       true,   2));
        result &= report("scene 3",test_intersect(scene, Ray(Vector(4, 1, 6),     Vector(-1, 7, -3)),     true,   4.03586));
        result &= report("scene 4",test_intersect(scene, Ray(Vector(15, 10.5, 3), Vector(-12, -3.5, -1)), true,   11.3111));
        result &= report("scene 5",test_intersect(scene, Ray(Vector(1, 4, 3),     Vector(0, -15, 0)),     false,  0)); // parallel to plane

        return result;
    }
} // namespace raytracer_test

int main()
{
    bool result = true;
    result &= raytracer_test::test_intersect_scene();
    raytracer_test::report("raytracer sub task c", result);
}
