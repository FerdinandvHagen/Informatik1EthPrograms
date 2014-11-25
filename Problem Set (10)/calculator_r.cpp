// Prog: calculator_r.cpp
// evaluate arithmetic expressions involving +, -, *, /, (, )
// over double operands, with right-to-left evaluation order

// Syntax in BNF:
// ---------------
// expression = term | term "+" expression | term "-" expression.
// term = factor | factor "*" term | factor "/" term.
// factor = "(" expression ")" | "-" factor | unsigned double.

#include<iostream>
#include<istream>
#include<sstream>
#include<cassert>

// declarations
// ------------

// PRE: is = expression...
// POST: expression e is extracted from is, and
//       its value is returned
double expression (std::istream& is);

// PRE: is = term...
// POST: term S is extracted from is, and
//       its value is returned
double term (std::istream& is);

// PRE: is = factor...
// POST: factor f is extracted from is, and
//       its value is returned
double factor (std::istream& is);


// definitions
// -----------

// POST: leading whitespace characters are extracted
//       from is, and the first non-whitespace character
//       is returned (0 if there is no such character)
char lookahead (std::istream& is)
{
  is >> std::ws;         // skip whitespaces
  if (is.eof())
    return 0;            // end of stream
  else
    return is.peek();    // next character in is
}

// expression = term | term "+" expression | term "-" expression.
double expression (std::istream& is) 
{
  double v = term(is);           // expression = t ... 
  char c = lookahead (is);
  if (c == '+')                  // expression = t + e
    v += expression(is >> c);
  else if (c == '-')             // expression = t - e
    v -= expression(is >> c);
  return v;                      // expression = t
}

// term = factor | factor "*" term | factor "/" term.
double term (std::istream& is) 
{
  double v = factor(is);         // term = f ...
  char c = lookahead (is);         
  if (c == '*')                  // term = f * t
    v *= term (is >> c);         
  else if (c == '/')             // term = f / t
    v /= term (is >> c);        
  return v;                      // term = f
}

// factor = "(" expression ")" | "-" factor | unsigned double.
double factor (std::istream& is) 
{
  double v;
  char c = lookahead (is);
  if (c == '(') {                // factor = (e)
    v = expression (is >> c);      
    is >> c;
    assert (c == ')');
  }
  else if (c == '-') {           // factor = -f
    v = -factor (is >> c);          
  }
  else {                         // factor = u
    is >> v;                       
    assert (!is.fail());
  }
  return v;
}

int main()
{
  std::stringstream input1 ("-(3-(4-5))*(3+4*5)/6"); // -15.33333
  std::stringstream input2 ("3-4-5");                // 4
  std::cout << expression (input1) << "\n";
  std::cout << expression (input2) << "\n";
  return 0;
}
