// Library to draw simple turtle graphics
// Simple interface using direct writing of bitmaps
//
// Copyright (c) 2014, Felix Friedrich, Department of Computer Science, ETH Zurich
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//
// *	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// *	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// *	Neither the name of the ETH Zurich nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <algorithm>
#include <stack>
#include <deque>
#include <fstream>
#include <cmath>
#include "bitmap.cpp"

const float Pi = std::atan(1)*4;

struct Vector
{
    float x;
    float y;

    Vector (float X, float Y): x(X), y(Y) {};
    Vector (const Vector& l): x(l.x), y(l.y) {};
    void rotate (float degrees);
};

void Vector::rotate (const float degrees)
{
    double sin= std::sin(degrees/180 * Pi);
    double cos= std::cos(degrees/180 * Pi);
    double nx = cos * x - sin * y;
    double ny = sin * x + cos * y;
    x = nx;
    y = ny;
}

class Image
{
public:
    int minx;
    int maxx;
    int miny;
    int maxy;
    std::deque<Vector> d;
    std::deque<float> c;

    Image(): minx(0), maxx(0), miny(0), maxy(0), d(), c() {}

    // width of rectangle embracing all points
    int Width() const
    {
        return maxx -minx+1;
    }

    // height of rectangle embracing all points
    int Height() const
    {
        return maxy-miny+1;
    }

    // add point to the fifo, adapt global bounds
    void Point(Vector p)
    {
        int x = int(p.x+0.5);
        int y = int(p.y+0.5);
        if (x < minx) minx = x;
        if (x > maxx) maxx = x;
        if (y < miny) miny = y;
        if (y > maxy) maxy = y;
        d.push_back(p);
    }

    // add a line to the fifo
    void Line (Vector p1, Vector p2, float col)
    {
        Point(p1);
        Point(p2);
        c.push_back(col);
    }

    // Bresenham algorithm for line drawing (from Informatik II D-BAUG eth, fof)
    void Line(Bitmap &bitmap, const Color& color, int x0, int y0, int x1, int y1)
    {
        int dx = fabs(x1-x0);
        int sx = x0<x1 ? 1 : -1;
        int dy = fabs(y1-y0);
        int sy = y0<y1 ? 1 : -1;
        int x=x0;
        int y=y0;
        int err = 0;

        if (dx>dy)
            for (;;)
            {
                bitmap(x,y) = color;
                if (x==x1 && y==y1) break;
                x += sx;
                err += dy;
                if (err*2 > dx)
                {
                    err -= dx;
                    y += sy;
                }
            }
        else
            for (;;)
            {
                bitmap(x,y) = color;
                if (x==x1 && y==y1) break;
                y += sy;
                err += dx;
                if (err*2 > dy)
                {
                    err -= dy;
                    x += sx;
                }
            }
    }

    Color GetColor (double v)
    {
        const Color Yellow = Red + Green;

        if (v <= 0.1)
            return White + (Yellow-White) * (v/0.1);
        else if (v <= 0.3)
            return Yellow + (Blue - Yellow) * ((v-0.1) / 0.2);
        else if (v <= 0.6)
            return Blue + (Green - Blue) * ((v - 0.3) / 0.3);
        else if (v <= 0.8)
            return Green + (Red - Green) * ((v - 0.6) / 0.2);
        else
            return Red + (Black - Red) * ((v - 0.8) / 0.2);
    }
    // render all lines to bitmap and store bitmap
    void StoreBmp()
    {
        Bitmap bitmap(Width(), Height());
        bitmap.Fill(Black);

        std::deque<float>::iterator itc = c.begin();
        for (std::deque<Vector>::iterator it = d.begin(); it!=d.end(); ++it)
        {
            Vector p1 = *it;
            ++it;
            Vector p2 = *it;
            int x1 = p1.x + 0.5 - minx;
            int x2 = p2.x + 0.5 - minx;
            int y1 = p1.y + 0.5 - miny;
            int y2 = p2.y + 0.5 - miny;
            float c= *itc; itc++;
            Line(bitmap,GetColor(c),x1,y1,x2,y2);
        }
        bitmap.Save("turtle_out.bmp");
    }

//    svg part commented, svg output renders very slowly only
//
//    void EmitPoint(std::ostream& fi, std::string name, float f)
//    {
//        fi << " " << name << "=\"" << int(f+0.5) << "\"";
//    }
//
//    void StoreSvg()
//    {
//        unsigned width = Width();
//        unsigned int height = Height();
//        std::ofstream fi("turtle_out.svg");
//        fi << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
//        fi << "<svg xmlns=\"http://www.w3.org/2000/svg\" \n";
//        fi << "version=\"1.1\" baseProfile=\"basic\"\n";
//        fi << " width=\""<< width << "px\"";
//        fi << " height=\"" << height << "px\"";
//        fi << " viewBox=\"" << minx << " " << miny;
//        fi << " " << width << " " << height << "\">\n";
//
//        for (std::deque<Vector>::iterator it = d.begin(); it!=d.end(); ++it)
//        {
//            Vector p1 = *it;
//            ++it;
//            Vector p2 = *it;
//            fi << "<line stroke=\"black\" stroke-width=\"1px\" ";
//            EmitPoint(fi,"x1",p1.x);
//            EmitPoint(fi,"y1",p1.y);
//            EmitPoint(fi,"x2",p2.x);
//            EmitPoint(fi,"y2",p2.y);
//            fi << "/>\n";
//        }
//        fi << "</svg>\n";
//    }

    ~Image()
    {
//      StoreSvg();
        StoreBmp();
    }
};

// simple turtle graphics interface
class Turtle
{

    Vector position;
    Vector direction;
    Image image;
    std::stack <Vector> s;
    float cx;
public:

    Turtle (): position(0,0), direction(10,0), image(), s(), cx(0) {};

    // move steps forward while drawing line
    void forward(const int steps)
    {
        Vector old = position;
        position.x += steps * direction.x;
        position.y += steps * direction.y;
        image.Line(old, position, cx);
    }

    // turn right by degrees
    void turn(const int degree)
    {
        direction.rotate(degree);
    }

    // jump forward without drawing line
    void jump(const int steps)
    {
        position.x += steps * direction.x;
        position.y += steps * direction.y;
    }

    // memorize current state (position, direction)
    void save()
    {
        s.push(direction);
        s.push(position);
    }

    // restore most recent state (position, direction)
    void restore()
    {
        position = s.top();
        s.pop();
        direction = s.top();
        s.pop();
    }

    void colorcycle()
    {
        cx += 0.0001; if (cx > 1) cx = 0;
    }

};

namespace turtle  // wrapper for acccess as for std::
{

    Turtle t; // global turtle objects. Stores data with destructor.

    // move steps forward while drawing a line
    void forward(const int steps)
    {
        t.forward(steps);
    }

    // move one step forward while drawing a line
    void forward()
    {
        forward(1);
    }

    // turn left by degrees
    void left(const int degrees)
    {
        t.turn(-degrees);
    }

    // turn right by degrees
    void right(const int degrees)
    {
        t.turn(degrees);
    }

    // move forward without drawing
    void jump(const int steps)
    {
        t.jump(steps);
    }

    // move forward one step without drawing
    void jump()
    {
        t.jump(1);
    }

    // save current state (direction, position) on stack
    void save()
    {
        t.save();
    }

    // restore current state (direction, position) from stack
    void restore()
    {
        t.restore();
    }

    void colorcycle()
    {
        t.colorcycle();
    }

}


