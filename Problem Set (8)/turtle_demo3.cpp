// Based on program source from Informatik f�r Mathematiker und Physiker, ETH Z�rich
// Courtesy by Bernd G�rtner

#include "turtle.cpp"

// rotate a path around the origin, using save and restore
int main()
{
  for (int i=0; i<20; ++i) {
    turtle::save();
    turtle::forward(2);
    turtle::left(45);
    turtle::forward(1);
    turtle::restore();
    turtle::left(18);
  }
  return 0;
}
