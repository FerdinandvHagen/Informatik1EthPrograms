// Based on program source from Informatik für Mathematiker und Physiker, ETH Zürich
// Courtesy by Bernd Gärtner


// Prog: dragon.cpp
// Draw turtle graphics for the Lindenmayer system with
// nontrivial productions X -> X+YF+, Y -> -FX-Y, initial
// word X and rotation angle 90 degrees

#include <iostream>
#include <string>
#include "turtle.cpp"

// POST: returns the production of c
std::string production (const char c)
{
  switch (c) {
  case 'X':
    return "X+YF+";
  case 'Y':
    return "-FX-Y";
  default:
    return std::string (1, c); // trivial production c -> c
  }
}

// POST: replaces all symbols in word according to their
//       production and returns the result
std::string next_word (const std::string& word)
{
  std::string next;
  for (unsigned int k = 0; k < word.length(); ++k)
    next += production (word[k]);
  return next;
}

// POST: draws the turtle graphic interpretation of word
void draw_word (const std::string& word)
{
  for (unsigned int k = 0; k < word.length(); ++k)
    switch (word[k]) {
    case 'F':
      turtle::forward(); // move one step forward
      break;
    case '+':
      turtle::left(90);  // turn counterclockwise by 90 degrees
      break;
    case '-':
      turtle::right(90); // turn clockwise by 90 degrees
    }
}

int main () {
  std::cout << "Number of iterations =? ";
  unsigned int n;
  std::cin >> n;

  std::string w = "X";  // w_0
  for (unsigned int i = 0; i < n; ++i)
    w = next_word (w);  // w_i -> w_{i+1}
  draw_word (w);        // draw w_n

  return 0;
}

