// Exercise 12: A Ray Tracer!
// Test program for sub task a): "vector operations"

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

    bool test_addition()
    {
        bool result = true;
        result &= report("add 1", is_equal(Vector(1, 2, 3) + Vector(3, 4, 6), Vector(4, 6, 9)));
        result &= report("add 2",is_equal(Vector(3, 4, 6) + Vector(1, 2, 3), Vector(4, 6, 9)));

        Vector v(1, 2, 3);
        result &= report("add 3",is_equal(v += Vector(3, 4, 6), Vector(4, 6, 9)));
        result &= report("add 4",is_equal(v, Vector(4, 6, 9)));

        return report("test_addition", result);
    }

    bool test_subtraction()
    {
        bool result = true;

        result &= report("subtract 1",is_equal(Vector(1, 2, 3) - Vector(3, 4, 6), Vector(-2, -2, -3)));
        result &= report("subtract 2",is_equal(Vector(3, 4, 6) - Vector(1, 2, 3), Vector(2, 2, 3)));

        Vector v1 = Vector(1, 2, 3);
        result &= report("subtract 3",is_equal(v1 -= Vector(3, 4, 6), Vector(-2, -2, -3)));
        result &= report("subtract 4",is_equal(v1, Vector(-2, -2, -3)));

        Vector v2 = Vector(1, 2, 3);
        result &= report("subtract 5",is_equal(v2 -= Vector(3, 4, 6), Vector(-2, -2, -3)));
        result &= report("subtract 6",is_equal(v2, Vector(-2, -2, -3)));

        return report("test_subtraction", result);
    }

    bool test_negation()
    {
        bool result = true;
        result &= is_equal(-Vector(1, 2, 3), Vector(-1, -2, -3));
        return report("test_negation", result);
    }

    bool test_scalar_multiplication()
    {
        bool result = true;

        result &= report("scalar mul 1",is_equal(Vector(1, 2, 3) * 1.5, Vector(1.5, 3.0, 4.5)));
        result &= report("scalar mul 2",is_equal(1.5 * Vector(1, 2, 3), Vector(1.5, 3.0, 4.5)));

        Vector v = Vector(1, 2, 3);
        result &= report("scalar mul 3",is_equal(v *= 1.5, Vector(1.5, 3.0, 4.5)));
        result &= report("scalar mul 4",is_equal(v, Vector(1.5, 3.0, 4.5)));

        return report("test_scalar_multiplication", result);
    }

    bool test_scalar_product()
    {
        bool result = true;

        result &= report("scalar product 1", is_equal(Vector(1, 2, 3) * Vector(3, 4, 6), 29));
        result &= report("scalar product 2",is_equal(Vector(3, 4, 6) * Vector(1, 2, 3), 29));

        return report("test_scalar_product", result);
    }

    bool test_norm()
    {
        bool result = true;

        result &= is_equal(norm(Vector(1, 2, 3)), 3.741657);

        return report("test_length", result);
    }

    bool test_normalize()
    {
        bool result = true;

        result &= is_equal(normalize(Vector(1, 2, 3)), Vector(0.267261, 0.534522, 0.801784));

        return report("test_normalize", result);
    }

} // namespace raytracer_test

int main()
{
    bool result = true;
    result &= raytracer_test::test_addition();
    result &= raytracer_test::test_subtraction();
    result &= raytracer_test::test_negation();
    result &= raytracer_test::test_scalar_multiplication();
    result &= raytracer_test::test_scalar_product();
    result &= raytracer_test::test_norm();
    result &= raytracer_test::test_normalize();
    raytracer_test::report("raytracer sub task a", result);
}
