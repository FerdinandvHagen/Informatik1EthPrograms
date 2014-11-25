// Based on program source from Informatik f�r Mathematiker und Physiker, ETH Z�rich
// Courtesy by Bernd G�rtner


#include "turtle.cpp"


// draw a regular 10-gon, but skip every second side
int main()
{
    for (unsigned int i = 0; i < 10; ++i) {
      if (i % 2 == 0)
        turtle::forward();
      else
	turtle::jump();
      turtle::left(36);
    }
    return 0;
}

