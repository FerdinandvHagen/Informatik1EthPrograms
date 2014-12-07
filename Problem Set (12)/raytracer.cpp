#include <cmath>
#include <cassert>
#include <algorithm>
#include <iostream>
#include "bitmap.cpp"

//PART A
struct Vector
{
    double x;
    double y;
    double z;

    //POST: vector should be initialized as null-vector
    Vector()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    //POST: coordinates (x,y,z) set to (x_, y_, z_)
    Vector(double x_, double y_, double z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
};

//POST: Returns the negation of the vector
Vector operator-(Vector vec)
{
    return Vector(-vec.x, -vec.y, -vec.z);
}

//POST: Subtracts one vector of another (v-w)
Vector operator-(Vector v, Vector w)
{
    return Vector(v.x - w.x, v.y - w.y, v.z - w.z);
}

//POST: Adds two vectors
Vector operator+(Vector v, Vector w)
{
    return Vector(v.x + w.x, v.y + w.y, v.z + w.z);
}

//POST: Subtracts two vectors and stores the result in the minuend
Vector& operator-=(Vector& v, Vector w)
{
    v.x -= w.x;
    v.y -= w.y;
    v.z -= w.z;
    return v;
}

//POST: Subtracts two vectors and stores the result in the minuend
Vector& operator+=(Vector& v, Vector w)
{
    v.x += w.x;
    v.y += w.y;
    v.z += w.z;
    return v;
}

//POST: Scalar product of two Vectors
double operator*(Vector v, Vector w)
{
    return (v.x*w.x) + (v.y*w.y) + (v.z*w.z);
}

//POST: Scalar multiplication of a vector with a scalar
Vector& operator*=(Vector& v, double r)
{
    v.x *= r;
    v.y *= r;
    v.z *= r;
    return v;
}

//POST: Scalar multiplication of a vector with a scalar
Vector operator*(Vector v, double r)
{
    return Vector(v.x * r, v.y * r, v.z * r);
}

//POST: Scalar multiplication of a vector with a scalar
Vector operator*(double r, Vector v)
{
    return Vector(v.x * r, v.y * r, v.z * r);
}

//POST: returns the Euclidean norm ||v|| of the vector v
double norm(const Vector& v)
{
    return sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
}

//POST: divides a Vector with a scalar
Vector operator/(Vector v, double r)
{
    return Vector(v.x/r, v.y/r, v.z/r);
}

//PRE: non-zero vector v
//POST: returns the normalized vector, ||v||=1
Vector normalize(const Vector& v)
{
    assert(v*v != 0);

    return v/norm(v);
}

//PART B
struct Ray
{
    Vector start;
    Vector direction; //INV: normalized

    //Constructor
    //PRE: non-zero vector d
    //POST: ray with offset s and normalized direction vector d
    Ray(Vector s, Vector d)
    {
        start = s;
        direction = normalize(d);
    }
};

struct Shape
{
    int type;               // INV: either 0 (sphere) or 1 (plane)
    Vector v;               // sphere: center, plane: plane normal
    double d;               // sphere: radius, plane: distance from origin
    Color ambientColor;     // ambient color ("Eigenleuchten")
    Color diffuseColor;     // diffuse color ("Diffuse Lichtreflektion")
    Color reflectionColor;  // reflection color ("Spiegelung")

    // POST: shape is initialized with type = Type, v = V
    // d = D, ambientColor = aC, diffuseColor=dC and
    // reflectionColor = rC
    Shape(int Type, Vector V, double D, Color aC, Color dC, Color rC)
    {
        type = Type;
        if(type == 1)
        {
            v = normalize(V);
        }
        else
        {
            v = V;
        }
        d = D;
        ambientColor = aC;
        diffuseColor = dC;
        reflectionColor = rC;
    }

    // POST: if there is an intersection between ray and
    // this shape, return true and return intersection
    // point as the parameter t in ray.start + ray.direction * t.
    // return false otherwise
    bool intersect(const Ray& ray, double& t) const
    {
        double t1, t2;
        if(type == 0)
        {
            //Type is sphere
            double discriminant = (ray.direction*(ray.start - v))*(ray.direction*(ray.start - v)) - (ray.start - v)*(ray.start - v) + d*d;
            if(discriminant < 0.0)
            {
                //no intersection
                return false;
            }

            t1 = -((ray.start - v)*ray.direction) + sqrt(discriminant);
            t2 = -((ray.start - v)*ray.direction) - sqrt(discriminant);
        }
        else
        {
            //Don't need it
            t2 = -1;

            t1 = (d - ray.start*v) / (ray.direction*v);
        }

        if(std::min(t1, t2) < 0)
        {
            if(std::max(t1, t2) < 0)
            {
                //t1 and t2 are smaller than zero so ignore it
                return false;
            }

            t = std::max(t1, t2);
            return true;
        }

        t = std::min(t1, t2);
        return true;
    }

    // PRE: vector "at" lies on the surface of this object
    // POST: return a normal vector of the shape at position "at"
    Vector get_normal(const Vector& at) const
    {
        if(type == 0)
        {
            return normalize(at - v);
        }
        else
        {
            return normalize(v);
        }
    }
};

struct Scene
{
    Vector cameraVector;        // camera position
    Vector lightVector;         // light position
    Color lightColor;           // light color
    unsigned int plane_width;   // observation window width
    unsigned int plane_height;  // observation window height
    std::vector<Shape> shapes;  // vector of shapes

    //POST: scene is initialized with cameraVector = cV, lightVector lV,
    // lightColor lC, plane_width w, plane_height h and
    // and empty vector shapes
    Scene(Vector cV, Vector lV, Color lC, int w, int h)
    {
        cameraVector = cV;
        lightVector = lV;
        lightColor = lC;
        plane_width = w;
        plane_height = h;
    }

    // POST: shape is added to the list of shapes
    void add_shape(const Shape& shape)
    {
        shapes.push_back(shape);
    }

    // POST: Return pointer to shape that has closest intersection with ray, if any
    // return null otherwise
    // t contains the parameter of the ray for the intersection point, if any
    const Shape* intersect(const Ray& ray, double& t) const
    {
        double t0 = +INFINITY;
        const Shape* s0 = NULL;

        int len = shapes.size();
        for(int i = 0; i < len; ++i)
        {
            if(shapes[i].intersect(ray, t) && t < t0)
            {
                s0 = &shapes[i];
                t0 = t;
            }
        }

        t = t0;
        return s0;
    }

    //POST: return a ray from camera origin through x,y on the pixel grid
    Ray create_ray(int x, int y) const
    {
        Vector pP = Vector((2.0 * x + 1.0 - plane_width) / (2.0 * plane_width), (-2.0 * y -1.0 + plane_height) / (2.0 * plane_height), 0);
        return Ray(cameraVector, pP - cameraVector);
    }

    //POST: return color returned by ray
    Color trace_ray(const Ray& ray, const int depth) const
    {
        Color c = Black;
        const Shape* s = NULL;
        double t = 0;

        s = intersect(ray, t);

        if(s != NULL)
        {
            // (i) ambient light
            c = c + s->ambientColor;

            // (ii) diffuse light and shadow
            Vector rT = ray.start + t * ray.direction;
            Vector v = lightVector - rT;
            Ray sR = Ray(rT, v);
            sR.start += v/1000; //hint b

            const Shape* t = NULL;
            double u = 0;
            t = intersect(sR, u);

            bool illuminated = (t == NULL) || (u > norm(v));

            if(illuminated)
            {
                Vector hN = normalize(s->get_normal(rT));
                c = c + lightColor*s->diffuseColor*(sR.direction*hN);
            }

            // (iii) specular highlighting
            Ray rR = Ray(rT, ray.direction - (2.0 * (s->get_normal(rT) * ray.direction) * s->get_normal(rT)));
            rR.start += rR.direction/1000;

            if(illuminated)
            {
                if(rR.direction * sR.direction > 0)
                {
                    c = c + lightColor * s->reflectionColor * pow(rR.direction*sR.direction, 16.0);
                }
            }

            //(iv) reflection recursion
            if(depth > 0)
            {
                Color rC = trace_ray(rR, depth - 1);
                c = c + rC * s->reflectionColor;
            }
        }
        return c;
    }

    //POST: run raytracer on bitmap
    void raytrace(Bitmap& bitmap, const int depth) const
    {
        for(int x = 0; x < plane_width; ++x)
        {
            for(int y = 0; y < plane_height; ++y)
            {
                bitmap(x,y) = trace_ray(create_ray(x, y), depth);
            }
        }
    }
};
