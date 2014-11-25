#include <iostream>
#include <fstream>
#include <cmath>

char decode_character(std::string value)
{
    char a = 0;
    for(int i = 0; i<8; i++)
    {
        a += (value[i] == '1') * std::pow(2, 7-i);
    }

    return a;
}

int main()
{
    std::string value;
    std::ifstream in("nzz.in");
    while(in >> value)
    {
        std::cout << decode_character(value);
    }
    return 0;
}
