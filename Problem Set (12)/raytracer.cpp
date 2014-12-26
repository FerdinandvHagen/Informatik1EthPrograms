#include <iostream>
#include <cmath>
#include <limits>
#include "bitmap.cpp"

//Part A

struct Vector
{
    double x;
    double y;
    double z;

    Vector()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vector(double x_, double y_, double z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
};

Vector operator-(const Vector &v)
{
    return Vector(-v.x, -v.y, -v.z);
}

Vector operator-(const Vector &v, const Vector &w)
{
    return Vector(v.x-w.x, v.y-w.y, v.z-w.z);
}

Vector operator+(const Vector &v, const Vector &w)
{
    return Vector(v.x+w.x, v.y+w.y, v.z+w.z);
}

Vector& operator-=(Vector &v, const Vector &w)
{
    v.x -= w.x;
    v.y -= w.y;
    v.z -= w.z;
    return v;
}

Vector& operator+=(Vector &v, const Vector &w)
{
    v.x += w.x;
    v.y += w.y;
    v.z += w.z;
    return v;
}

double operator*(const Vector &v, const Vector &w)
{
    return v.x*w.x+v.y*w.y+v.z*w.z;
}

Vector& operator *= (Vector &v, const double &r)
{
    v.x *= r;
    v.y *= r;
    v.z *= r;
    return v;
}

Vector operator*(const Vector &v, const double &r)
{
    return Vector(v.x*r, v.y*r, v.z*r);
}

Vector operator*(const double &r, const Vector &v)
{
    return v*r;
}

//Returns the length of the vector
double norm(const Vector &v)
{
    return std::sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

//Returns the normalized Vector e.g. an Vector with the same direction, but length == 1
Vector normalize(const Vector &v)
{
    double n = norm(v);
    return Vector(v.x/n, v.y/n, v.z/n);
}

//Part b

struct Ray
{
    Vector start;
    Vector direction;

    Ray(Vector s, Vector d)
    {
        start = s;
        direction = normalize(d);
    }
};

struct Shape
{
    int type;//0 = sphere, 1 = plane
    Vector v;//sphere: center, plane: plane normal
    double d;//sphere: radius, plane: distance from origin

    Color ambientColor;
    Color diffuseColor;
    Color reflectionColor;

    Shape(int Type, Vector V, double D, Color aC, Color dC, Color rC)
    {
        type = Type;
        if(type == 1) v = normalize(V);
        else v = V;
        d = D;
        ambientColor = aC;
        diffuseColor = dC;
        reflectionColor = rC;
    }

    bool intersect(const Ray& ray, double& t)const
    {
        double t1, t2;
        if(type == 0)
        {
            Vector dv = ray.start-v;//delta v
            double discriminant = (ray.direction * dv) * (ray.direction * dv) - (dv * dv) + d * d;

            if(discriminant < 0) return false;//No intersection

            t1 = (-dv * ray.direction) + std::sqrt(discriminant);
            t2 = (-dv * ray.direction) - std::sqrt(discriminant);
        }
        else
        {
            t2 = -1;//it's a plane, only one intersection possible, therefore isn't needed anymore
            t1 = (d - ray.start * v) / (ray.direction * v);
        }

        if(t1 < 0 && t2 < 0) return false;//both are smaller zero, aren't needed

        if((t1 < 0 && t2 > 0) || t2 < t1) t = t2;
        if((t2 < 0 && t1 > 0) || (t1 < t2 && t1 > 0)) t = t1;
        return true;
    }

    Vector get_normal(const Vector& at) const
    {
        if(type == 1) return normalize(v);
        else return normalize(at-v);
    }
};

//Part c

struct Scene{
    Vector cameraVector; //Camera position
    Vector lightVector; //light position
    Color lightColor; //light color
    unsigned int plane_width; //observation windows width
    unsigned int plane_height; //observation window height
    std::vector<Shape> shapes; //vector of shapes

    Scene(Vector cV, Vector lV, Color lC, int w, int h){
        cameraVector = cV;
        lightVector = lV;
        lightColor = lC;
        plane_width = w;
        plane_height = h;
    }

    void add_shape(const Shape& shape){
        shapes.push_back(shape);
    }

    const Shape* intersect(const Ray& ray, double& t) const{
        double t0 = std::numeric_limits<double>::max();
        const Shape* s0 = NULL;
        for(int i = 0; i < shapes.size(); i++){
            if(shapes[i].intersect(ray, t) && t < t0){
                s0 = &shapes[i];
                t0 = t;
            }
        }
        t = t0;
        return s0;
    }

    //Part d
    Ray create_ray(int x, int y) const{
        Vector td = Vector((2.0*x+1.0-plane_width)/(2.0*plane_width), (-2.0*y-1.0+plane_height)/(2.0*plane_height), 0);
        return Ray(cameraVector, td - cameraVector);//d - cameraVector means direction from cameravector to the pixel with the coordinates of d
    }

    //Part e
    Color trace_ray(const Ray& ray, const int depth) const{
        Color c = Black;
        const Shape* shape = NULL;
        double t = 0;
        shape = intersect(ray, t);

        if(shape != NULL){

            //(i)
            c = c + shape->ambientColor;

            //(ii)
            Vector Rt = ray.start + t*ray.direction;
            Vector v = lightVector-Rt;  //Shadow ray direction

            Ray sR = Ray(Rt, v);
            sR.start += normalize(v)*(1.0/1000);//hint

            const Shape* T = NULL;
            double u = 0;
            T = intersect(sR, u);

            bool illuminated = false;
            if(T == NULL || u > norm(v)) illuminated = true;

            if(illuminated){
                Vector hN = normalize(shape->get_normal(Rt));
                c = c + lightColor*shape->diffuseColor*(sR.direction*hN);
            }

            //(iii)
            Ray rR = Ray(Rt, ray.direction-(2.0*(shape->get_normal(Rt)*ray.direction)*shape->get_normal(Rt)));//hint
            rR.start += normalize(rR.direction)*(1.0/1000);

            if(illuminated){
                if(rR.direction*sR.direction > 0)
                    c = c + lightColor * shape->reflectionColor * std::pow(rR.direction*sR.direction,16.0);
            }

            //(iv)
            if(depth > 0){
                Color rC = trace_ray(rR, depth-1);
                c = c + rC * shape->reflectionColor;
            }
        }

        return c;

    }

    void raytrace(Bitmap& bitmap, const int depth) const{
        for(int i = 0; i < plane_width; ++i){
            for(int j = 0; j < plane_height; ++j){
                bitmap(i, j) = trace_ray(create_ray(i, j), depth);
            }
        }
    }


};
