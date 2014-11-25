// Based on program source from Informatik für Mathematiker und Physiker, ETH Zürich
// Courtesy by Bernd Gärtner


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

