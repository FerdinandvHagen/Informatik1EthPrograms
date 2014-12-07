#include <iostream>
#include "bitmap.cpp"
#include <cmath>
#include <cassert>


struct cint
{
    //z = real + i*imaginary
    double real;
    double imaginary;
};

cint operator+(const cint a, const cint b){
    cint sum;
    sum.real = a.real + b.real;
    sum.imaginary = a.imaginary + b.imaginary;
    return sum;
}

cint operator-(const cint a, const cint b){
    cint difference;
    difference.real = a.real - b.real;
    difference.imaginary = a.imaginary - b.imaginary;
    return difference;
}

cint operator*(const cint a, const cint b){
    cint mul;
    mul.real = a.real*b.real - a.imaginary*b.imaginary;
    mul.imaginary = a.real*b.imaginary + a.imaginary*b.real;
    return mul;
}

cint operator/(const cint a, const cint b){
    //first calculate 1/b
    cint z;
    z.real = b.real / (b.real*b.real + b.imaginary*b.imaginary);
    z.imaginary = -b.imaginary / (b.real*b.real + b.imaginary*b.imaginary);
    return a * z;
}

bool operator== (const cint a, const cint b)
{
    return (a.real == b.real) && (a.imaginary == b.imaginary);
}

bool operator!= (cint a, cint b)
{
    return !(a == b);
}

std::ostream& operator<< (std::ostream& out, const cint r)
{
    return out << r.real << "+i" << r.imaginary;
}

double abs(cint z)
{
    return sqrt((z.real*z.real) + (z.imaginary*z.imaginary));
}

//Expect: x+iy where x, y are of type double
std::istream& operator >> (std::istream& in, cint& r)
{
    char c;
    return in >> r.real >> c >> c >> r.imaginary;
}

int iterateMandel(cint c)
{
    const int max_cycles = 700;
    cint zn = {0,0};
    for (int i = 0; i<max_cycles; i++)
    {
        if(abs(zn) > 40)
        {
            return i;
        }
        zn = (zn*zn) + c;
    }
    return max_cycles;
}

float getFloatFromValues(int a, int b, int value)
{
    //Normalize Value!

    //Out of bounds
    if(value < a || value > b)
    {
        return 0.0;
    }

    value -= (a + (b-a)/2);

    float normalized = (float)value / (b-a); //This should be now -1 < normalized < 1

    assert (normalized < 1.0 && normalized > -1.0);

    return -(normalized*normalized) + 1;
}

Color MandelColor(cint c)
{
    int iterations = iterateMandel(c);
    if(iterations > 640)
    {
        return Black;
    }
    else
    {
        float blue = getFloatFromValues(0, 34/64*640, iterations);
        float green = getFloatFromValues(22/64*640, 640, iterations);
        float red = 0;

        Color color = Color(red, green, blue);
        return color;
    }
}



int main ()
{
	Bitmap bitmap (10000, 10000);

	Color top = Red;
	Color bottom = Green;

    double re_start = -200;
    double re_end = 1;

    double im_start = -1.5;
    double im_end = 150;

    double re = re_start;
    double im = im_start;

    double re_step = (re_end - re_start) / bitmap.GetHeight();
    double im_step = (im_end - im_start) / bitmap.GetWidth();

	for (int y = 0; y != bitmap.GetHeight (); ++y)
	{
        im = im_start;
		for (int x = 0; x != bitmap.GetWidth(); ++x)
        {
            cint c = {re,im};
            bitmap (x, y) = MandelColor(c);
            im += im_step;
        }
        re += re_step;
	}

	bitmap.Save ("test.bmp");
}



