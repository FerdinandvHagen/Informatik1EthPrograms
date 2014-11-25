#include <iostream>
#include <cassert>
#include <vector>

typedef std::string::iterator Iterator;

//return true if string at first1, last1 is lexicographically
//smaller than string at first, last2
bool lexicographic_compare(const Iterator first1, const Iterator last1,
                           const Iterator first2, const Iterator last2)
{
    Iterator f1 = first1;
    Iterator f2 = first2;

    do
    {
        if(*f1 > *f2)
        {
            return false;
        }
    }
    while(++f1 <= last1 && ++f2 <= last2);

    if(f2 == last2)
    {
        return false;
    }

    return true;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::string> strings(n);

    for(std::vector<std::string>::iterator it = strings.begin(); it < strings.end(); it++)
    {
        std::cin >> *it;
    }

    std::string minimum = strings[0];
    for(int i = 0; i < strings.size(); i++)
    {
        if(lexicographical_compare(minimum.begin(), minimum.end(), strings[i].begin(), strings[i].end()))
        {
            minimum = strings[i];
        }
    }

    std::cout << minimum;
    return 0;
}
