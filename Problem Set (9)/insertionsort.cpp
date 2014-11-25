#include <iostream>
#include <cassert>


void input(int* const begin, int* const end)
{
    assert(begin < end);

    std::cout << "Please enter " << end - begin + 1 << " numbers" << std::endl;

    int* ptr = begin;
    do
    {
        std::cin >> *ptr++;
    }
    while(ptr <= end);
}

void output(int* const begin, int* const end)
{
    assert(begin < end);

    int* ptr = begin;
    do
    {
        std::cout << *ptr++ << std::endl;
    }
    while(ptr <= end);
}

void swap(int* const element1, int* const element2)
{
    int temp = *element2;
    *element2 = *element1;
    *element1 = temp;
}

int* minimum(int* const begin, int* const end)
{
    assert(begin < end);
    int* min = begin;

    int* ptr = begin;
    do
    {
        if(*ptr < *min)
        {
            min = ptr;
        }
    }
    while(++ptr <= end);

    return min;
}

void swapWithMinimum(int* const begin, int* const end)
{
    assert(begin < end);
    swap(begin, minimum(begin, end));
}

void sort(int* const begin, int* const end)
{
    if(begin == end)
    {
        return;
    }

    swapWithMinimum(begin, end);

    sort(begin+1, end);
}



int main ()
{
    int data[10];
    input(&data[0], &data[9]);

    sort(&data[0], &data[9]);

    output(&data[0], &data[9]);
    return 0;
}
