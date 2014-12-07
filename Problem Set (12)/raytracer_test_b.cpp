// Exercise 12: A Ray Tracer!
// Test program for sub task b): "Ray Intersection and Shapes"
//
// Version 2, changes:
// 04.12.2014 get_normal test: Accept any normal vector,
//            not just vectors of size 1

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

    bool intersects_at(const Shape& shape, const Ray& ray, bool intersects_expect, double t_expect)
    {
        double t_res;
        bool intersects_res = shape.intersect(ray, t_res);
        return intersects_res == intersects_expect && (!intersects_res || is_equal(t_res, t_expect));
    }

    bool test_intersect_sphere()
    {
        bool result = true;

        Shape shape(0, Vector(0, 0, 0), 1, White, White, White);

        Ray ray(Vector(4, -3, 2), Vector(-4, 3, -2));
        result &= report("intersect sphere 1",intersects_at(shape, ray, true, 4.38516));

        Ray ray2(Vector(4, -3, 2), Vector(-3, 3, -2));
        result &= report("intersect sphere 2",intersects_at(shape, ray2, true, 4.69042));

        Ray ray3(Vector(4, -3, 2), Vector(-2.5, 3, -2));
        result &= report("intersect sphere 3",intersects_at(shape, ray3, false, -0));

        return report("test_intersect_sphere",result);
    }

    bool test_intersect_plane()
    {
        bool result = true;

        Shape shape(1, Vector(-0.9701, 0, 0.2425), 4, White, White, White);
        Ray ray(Vector( 3.5, 0, 0), Vector(-1, 0, 0.2));
        result &= report("intersect plane 1",intersects_at(shape, ray, true, 7.40409));

        Ray ray2(Vector(2.5, 0, 0), Vector(2, 0.1, -0.4));
        result &= report("intersect plane 2",intersects_at(shape, ray2, false, 0));

        Shape shape2(1, Vector(0, 0, 1), -1, White, White, White);
        Ray ray3(Vector(0, 0, 2), Vector(2, 4, 2));
        result &= report("intersect plane 3",intersects_at(shape2, ray3, false, 0));

        Ray ray4(Vector(0, 0, 1), Vector(2, 4, 1));
        result &= report("intersect plane 3",intersects_at(shape2, ray4, false, 0));

        return report("test_intersect_plane",result);
    }

    bool test_normal_sphere()
    {
        bool result = true;

        Shape shape(0, Vector(1, 0, -0.25), 1, White, White, White);
        result &= report("normal sphere 1",is_equal(normalize(shape.get_normal(Vector(1,0,0.75))), Vector(0,0,1)));
        result &= report("normal sphere 2",is_equal(normalize(shape.get_normal(Vector(0.95,0.75,0.409545))), Vector(-0.05,0.75,0.659545)));

        return report("test_normal_sphere",result);
    }

    bool test_normal_plane()
    {
        bool result = true;

        Vector v(-0.05, 0.95, 0.23);
        Shape shape(1, v, -0.45, White, White, White);
        result &= report("normal plane 1",is_equal(normalize(shape.get_normal(Vector(0.5,1,-5.97826))), normalize(v)));
        result &= report("normal plane 2",is_equal(normalize(shape.get_normal(Vector(0,0,-1.95652))),  normalize(v)));

        return report("test_normal_plane",result);
    }
} // namespace raytracer_test

int main()
{
    bool result = true;
    result &= raytracer_test::test_intersect_sphere();
    result &= raytracer_test::test_intersect_plane();
    result &= raytracer_test::test_normal_sphere();
    result &= raytracer_test::test_normal_plane();
    raytracer_test::report("raytracer sub task b", result);
}
