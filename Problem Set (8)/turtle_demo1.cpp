// Based on program source from Informatik f�r Mathematiker und Physiker, ETH Z�rich
// Courtesy by Bernd G�rtner


#include "turtle.cpp"

// draw a regular pentagon
int main()
{
    for (unsigned int i = 0; i < 5; ++i) {
        turtle::forward();
        turtle::left(72);
    }
    return 0;
}

