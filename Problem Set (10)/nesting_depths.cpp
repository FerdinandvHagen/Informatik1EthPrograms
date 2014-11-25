#include<iostream>
#include<istream>
#include<sstream>
#include<cassert>

char lookahead (std::istream& is)
{
  is >> std::ws;         // skip whitespaces
  if (is.eof())
    return 0;            // end of stream
  else
    return is.peek();    // next character in is
}

int depth_count(int depth, std::istream& is){

    char c = lookahead(is);

    if(c == 0)
    {
        assert(depth == 0);
        return 0;
    }

    if(c == '(')
    {
        return depth_count(depth + 1, is >> c);
    }

    if(c == ')')
    {
        int other = depth_count(depth - 1, is >> c);
        if(other > depth)
            return other;
        else
            return depth;
    }

    return depth_count(depth, is >> c);
}

int compute_nesting_depth(std::istream& is)
{
    return depth_count(0, is);
}

int main()
{
    std::stringstream input1 ("-(3-(4-5))*(3+4*5)/6"); // -15.33333
    std::stringstream input2 ("(((((((())(())))))))");                // 4
    std::cout << compute_nesting_depth(input1) << "\n";
    std::cout << compute_nesting_depth(input2) << "\n";
}
