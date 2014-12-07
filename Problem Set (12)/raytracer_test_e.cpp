// Exercise 12: Raytracer
// Test program for sub task e): "Raytracing"

#include <iostream>
#include <cmath>
#include <iomanip>
#include "raytracer.cpp"


namespace raytracer_test
{
    const double eps = 0.0001;

    bool is_equal(float f1, float f2)
    {
        return fabs(f1 - f2) <= ((fabs(f1) > fabs(f2) ? fabs(f2) : fabs(f1)) * eps);
    }

    bool is_equal(Color c1, Color c2)
    {
        return is_equal(c1.r, c2.r) && is_equal(c1.g, c2.g) && is_equal(c1.b, c2.b);
    }

    bool report(std::string name, bool result)
    {
        std::cout << "test " << name << " ";
        if (result)
            std::cout << "passed.\n";
        else
            std::cout << "failed.\n";
        return result;
    }

    void gen_image_data(const Bitmap& bitmap)
    {
        std::cout << "\n\nbegin\n\n";
        const int sampling_rate_x = bitmap.GetWidth()  / 10;
        const int sampling_rate_y = bitmap.GetHeight() / 10;

        std::cout << std::setprecision(6);

        for(unsigned int x = 0; x < bitmap.GetWidth(); x += sampling_rate_x)
        {
            for(unsigned int y = 0; y < bitmap.GetHeight(); y += sampling_rate_y)
            {
                Color c = AdjustColor(bitmap(x,y));
                std::cout << c.r << "," << c.g << "," << c.b << ",";
            }
        }
        std::cout << "\n\nend\n\n";
    }


    bool test_scene(std::string test_name, const Bitmap& bitmap, const float colors[])
    {
        //gen_image_data(bitmap);

        const int sampling_rate_x = bitmap.GetWidth()  / 10;
        const int sampling_rate_y = bitmap.GetHeight() / 10;

        bool result = true;

        int color = 0;
        for(unsigned int x = 0; x < bitmap.GetWidth(); x += sampling_rate_x)
        {
            for(unsigned int y = 0; y < bitmap.GetHeight(); y += sampling_rate_y)
            {
                Color color_res      = AdjustColor(bitmap(x,y));
                Color color_expected = Color(colors[color], colors[color+1], colors[color+2]);
                if (!is_equal(color_res, color_expected))
                {
                    result = false;
                    //break;
                }
                color += 3;
            }
        }

        return result &= report(test_name,result);
    }

    bool test_ambient_sphere()
    {

        const double dist = 1; //  distance from pixel plane
        const int w = 800;
        const int h = 800;
        Scene scene(Vector(0, 0, -dist), Vector(10, 10, -1), White, w, h);

        scene.add_shape(Shape(0, Vector(0, 0, 2), 1, 0.5 * Red, Black, Black));

        Bitmap bitmap(w, h);
        scene.raytrace(bitmap, 0);
        bitmap.Save("rays_ambient_sphere.bmp");

        float image_data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

        return test_scene("ambient_sphere", bitmap, image_data);
    }

    bool test_diffuse_plane()
    {

        const double dist = 0.5; //  distance from pixel plane
        const int w = 800;
        const int h = 800;
        Scene scene(Vector(0, 0, -dist), Vector(10, 10, -1), White, w, h);

        scene.add_shape(Shape(1, Vector(0.1, 0.9, -0.1), -5.0, 0.2 * Green, 0.7*Green, Black));

        Bitmap bitmap(w, h);
        scene.raytrace(bitmap, 0);
        bitmap.Save("rays_diffuse_plane.bmp");

        float image_data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0.235277,0,0,0.470728,0,0,0.598068,0,0,0.66605,0,0,0.705371,0,0,0.73008,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.201886,0,0,0.473655,0,0,0.613576,0,0,0.683041,0,0,0.721036,0,0,0.743981,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.47443,0,0,0.630237,0,0,0.70128,0,0,0.737598,0,0,0.758495,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.470681,0,0,0.647333,0,0,0.720483,0,0,0.754895,0,0,0.773514,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.458581,0,0,0.663284,0,0,0.74004,0,0,0.772621,0,0,0.788858,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.433535,0,0,0.675132,0,0,0.75883,0,0,0.790264,0,0,0.80425,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.393311,0,0,0.678215,0,0,0.775011,0,0,0.807033,0,0,0.819292,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.341991,0,0,0.666897,0,0,0.785892,0,0,0.821788,0,0,0.833435,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.288629,0,0,0.637259,0,0,0.788105,0,0,0.833015,0,0,0.845954,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.240879,0,0,0.590515,0,0,0.77836,0,0,0.838892,0,0,0.855954,0};

        return test_scene("diffuse_plane", bitmap, image_data);
    }

    bool test_shadows()
    {

        const double dist = 0.5; //  distance from pixel plane
        const int w = 800;
        const int h = 800;
        Scene scene(Vector(0, 0, -dist), Vector(3, 3, 0), White, w, h);

        const Color Yellow = Red + Green;
        scene.add_shape(Shape(1, Vector(0, 1, 0), -2.7, 0.2 * Blue, 0.7*Blue, Black));
        scene.add_shape(Shape(1, Vector(1, 0, 0), -3.5, 0.2 * Green, 0.7*Green, Black));
        scene.add_shape(Shape(0, Vector(-0.5, 0.3, 4),     1, 0.05*Yellow, 0.4*Yellow, Black));

        Bitmap bitmap(w, h);
        scene.raytrace(bitmap, 0);
        bitmap.Save("rays_shadows.bmp");

        float image_data[] = {0,0.833865,0,0,0.835159,0,0,0.830429,0,0,0.820069,0,0,0.804882,0,0,0.785927,0,0,0.764335,0,0,0.741167,0,0,0.71732,0,0,0,0.642664,0,0.791292,0,0,0.799678,0,0,0.800243,0,0,0.792922,0,0,0.778542,0,0,0.75858,0,0,0.734786,0,0,0.708835,0,0,0.682117,0,0,0,0.666613,0,0.712305,0,0,0.730325,0,0,0.739703,0,0,0.738954,0,0,0.728201,0,0,0.709124,0,0,0.2,0,0,0.656374,0,0,0,0.643944,0,0,0.6915,0,0.579143,0,0,0.60398,0,0,0.622725,0,0,0.631836,0,0,0.629279,0,0,0.615648,0,0,0.2,0,0,0,0.2,0,0,0.672312,0,0,0.716863,0,0.394399,0,0,0.412733,0,0,0.429834,0,0,0.442798,0,0.265433,0.265433,0,0.131787,0.131787,0,0,0,0.462281,0,0,0.620342,0,0,0.700446,0,0,0.742006,0,0,0,0,0,0,0,0,0,0,0,0,0.446733,0.446733,0,0.289195,0.289195,0,0,0,0.476513,0,0,0.645429,0,0,0.726728,0,0,0.765971,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.201812,0,0,0.482555,0,0,0.663832,0,0,0.749056,0,0,0.787551,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.201716,0,0,0.478676,0,0,0.672264,0,0,0.765115,0,0,0.805373,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.201584,0,0,0.466008,0,0,0.668978,0,0,0.7729,0,0,0.818074,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.201443,0,0,0.447747,0,0,0.654674,0,0,0.771325,0,0,0.824541};

        return test_scene("shadows", bitmap, image_data);
    }

    bool test_reflection_spheres()
    {

        const double dist = 1; //  distance from pixel plane
        const int w = 800;
        const int h = 800;
        Scene scene(Vector(0, 0, -dist), Vector(10, 10, -1), White, w, h);

        const Color Yellow = Red + Green;
        scene.add_shape(Shape(0, Vector(0, -1.5, 4),     0.5, 0.05*Yellow, 0.4*Yellow, White));
        scene.add_shape(Shape(0, Vector(0, 1.5, 4),     0.5, 0.05*Red, 0.4*Red, White));
        scene.add_shape(Shape(0, Vector(-1.5, 0, 4),     0.5, 0.05*Blue, 0.4*Blue, White));
        scene.add_shape(Shape(0, Vector(1.5, -0, 4),     0.5, 0.05*Green, 0.4*Green, White));

        Bitmap bitmap(w, h);
        scene.raytrace(bitmap, 10);
        bitmap.Save("rays_reflection_spheres.bmp");

        float image_data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.05,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.335599,7.97764e-06,7.97764e-06,0.242215,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.324231,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.05,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.05,0.05,0,0,0,0,0,0,0,0.316399,8.88668e-07,8.88668e-07,0.103009,9.44235e-15,9.44235e-15,0.05,0,0,0,0,0,0,0,0,0,0,0,0.335805,0.335805,0,0.242456,0.242456,8.31748e-06,0.05,0.05,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.05,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.00618e-15,0.337308,1.00618e-15,7.9607e-15,0.10274,7.9607e-15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.69545e-07,0.314867,1.69545e-07,0,0,0,0,0,0,0,0,0,0,0,0};

        return test_scene("reflection_spheres", bitmap, image_data);
    }

    bool test_reflection_on_plane()
    {

        const double dist = 1; //  distance from pixel plane
        const int w = 800;
        const int h = 800;
        Scene scene(Vector(0, 0, -dist), Vector(10, 1, -10), White, w, h);

        const Color Yellow = Red + Green;

        scene.add_shape(Shape(1, Vector(0, 1, 0), -0.75, 0.2 * Blue, 0.7*Blue, White));
        scene.add_shape(Shape(0, Vector(-0.5, 0.3, 4),     0.5, 0.05*Yellow, 0.4*Yellow, Black));

        Bitmap bitmap(w, h);
        scene.raytrace(bitmap, 10);
        bitmap.Save("rays_reflection_on_plane.bmp");

        float image_data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.200905,0,0,0.256988,0,0,0.270012,0,0,0.27573,0,0,0.278936,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.200939,0,0,0.258256,0,0,0.271032,0,0,0.276546,0,0,0.27961,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.200969,0,0,0.259535,0,0,0.272063,0,0,0.277369,0,0,0.280289,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.200992,0,0,0.260818,0,0,0.273105,0,0,0.2782,0,0,0.280973,0,0,0,0,0,0,0,0,0,0,0,0,0.3786,0.3786,0,0.306976,0.306976,0,0,0,0.262099,0,0,0.274155,0.243833,0.243833,0.279038,0.390165,0.390165,0.281663,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.201013,0,0,0.26337,0,0,0.275211,0,0,0.279883,0,0,0.282358,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.201009,0,0,0.264622,0,0,0.276273,0,0,0.280733,0,0,0.283057,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.200995,0,0,0.265846,0,0,0.277338,0,0,0.281588,0,0,0.28376,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.200973,0,0,0.267031,0,0,0.278404,0,0,0.282448,0,0,0.284468,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.200944,0,0,0.268164,0,0,0.279469,0,0,0.283312,0,0,0.285179};

        return test_scene("reflection_on_plane", bitmap, image_data);
    }

    bool test_reflection_large()
    {

        const double dist = 1; //  distance from pixel plane
        int w = 800;
        int h = 800;
        Scene scene(Vector(0, 0, -dist), Vector(10, 10, -1), White, w, h);

        const Color Yellow    = Red + Green;
        const Color WarmWhite = 0.5 * White + 0.3 * Yellow;
        const Color LightBlue = 0.25 * White + 0.5 * Blue;

        scene.add_shape(Shape(0, Vector(0, 0, 4),     0.5, 0.05 * Yellow,    0.1*Yellow,    White));
        scene.add_shape(Shape(0, Vector(1, 1, 4),     0.2, 0.1  * White,     0.2*Green,     0.6 * Yellow));
        scene.add_shape(Shape(0, Vector(1, 1.3, 4.1), 0.2, 0.1  * White,     0.2*Green,     0.6 * Yellow));
        scene.add_shape(Shape(0, Vector(-1, -2, 4),   1.5, 0.1  * White,     Blue,          0.5*White));
        scene.add_shape(Shape(0, Vector(-3, 3, 16),   4.0, 0.1  * Blue,      0.8*WarmWhite, 0.7*LightBlue));
        scene.add_shape(Shape(1,  Vector(0, 1, 0),    -1.0, 0.2  * WarmWhite, WarmWhite,     Black));

        Bitmap bitmap(w, h);
        scene.raytrace(bitmap, 5);
        bitmap.Save("rays_reflect_large.bmp");

        float image_data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.164908,0.164908,0.103068,0.577797,0.577797,0.361123,0.666532,0.666532,0.416583,0.697499,0.697499,0.435937,0.712472,0.712472,0.445295,0,0,0,0,0,0,0.00858063,0.00858063,0.105363,0.00784362,0.00784362,0.104902,0.0671019,0.0671019,0.225816,0.165097,0.165097,0.103185,0.592031,0.592031,0.370019,0.1,0.1,0.363454,0.705334,0.705334,0.440834,0.718618,0.718618,0.449136,0,0,0,0.23144,0.23144,0.24465,0.334429,0.334429,0.309018,0.273286,0.273286,0.270804,0.229672,0.229672,0.360955,0.0910134,0.0910134,0.27065,0.606685,0.606685,0.379178,0.1,0.1,0.674184,0.71328,0.71328,0.4458,0.724829,0.724829,0.453018,0,0,0,0.468253,0.468253,0.392658,0.511584,0.511584,0.421136,0.469916,0.469916,0.432843,0.404395,0.404395,0.483499,0.166366,0.166366,0.325025,0.255604,0.255604,0.310165,0.100777,0.100777,0.878294,0.721331,0.721331,0.450832,0.731102,0.731102,0.456939,0,0,0,0.535334,0.535334,0.434584,0.644126,0.644126,0.56006,0.606513,0.606513,0.621491,0.508959,0.508959,0.556573,0.078,0.078,0.1525,0.636905,0.636905,0.398065,0.402766,0.402766,1,0.72948,0.72948,0.455925,0.737434,0.737434,0.460896,0,0,0,0,0,0,0.605777,0.605777,0.478611,0.566499,0.566499,0.454065,0.703839,0.703839,0.463891,0.349332,0.349332,0.168132,0.652214,0.652214,0.407634,0.1,0.1,1,0.737719,0.737719,0.461075,0.74382,0.74382,0.464888,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.165476,0.165476,0.103422,0.667425,0.667425,0.41714,0.732753,0.732753,0.45797,0.746039,0.746039,0.466274,0.750258,0.750258,0.468911,0,0,0,0,0,0,0,0,0,0.534323,0.551118,0.1,0,0,0,0.165399,0.165399,0.103374,0.682312,0.682312,0.426445,0.744277,0.744277,0.465173,0.754428,0.754428,0.471517,0.756743,0.756743,0.472964,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.165276,0.165276,0.103298,0.69661,0.69661,0.435381,0.755846,0.755846,0.472404,0.762874,0.762874,0.476796,0.76327,0.76327,0.477043,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.165116,0.165116,0.103198,0.710016,0.710016,0.44376,0.767411,0.767411,0.479632,0.771365,0.771365,0.482103,0.769832,0.769832,0.481145};

        return test_scene("reflect_large", bitmap, image_data);
    }
} // namespace raytracer_test

int main()
{
    bool result = true;
    result &= raytracer_test::test_ambient_sphere();
    result &= raytracer_test::test_diffuse_plane();
    result &= raytracer_test::test_shadows();
    result &= raytracer_test::test_reflection_spheres();
    result &= raytracer_test::test_reflection_on_plane();
    result &= raytracer_test::test_reflection_large();
    raytracer_test::report("raytracer sub task e", result);
}
