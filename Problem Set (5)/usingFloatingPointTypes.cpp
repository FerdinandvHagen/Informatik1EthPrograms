#include <iostream>
#include <cmath>

int main()
{
    std::cout << "Please enter x and y coordinate: " << std::endl;
    double x, y;
    std::cin >> x >> y;


    if(std::abs(2.1*x+0.5-y)<0.0001)
    {
        std::cout << "The Point x: " << x << " with y: " << y << " is on the line" << std::endl;
    }
    else
    {
        std::cout << "The Point x: " << x << " with y: " << y << " is not on the line" << std::endl;
    }
}
