#include <iostream>
#include <cmath>
#include <cassert>


//Count the Leap Years from 1900 to the given Year
int countLeapYears(int end)
{
    return (end/4) + (end/400) + (1899/100) - (end/100) - (1899/4) - (1899/400);
}

//Check whether the given year is a leap year
bool isLeapYear(int year)
{
    if(year % 400 == 0 || ((year % 4 == 0)&&(year % 100 != 0)))
    {
        return true;
    }
    return false;
}

//Returns the Days in the given month and year
int getDays(int month, int year)
{
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        return 31;
    }
    if(month == 2)
    {
        if(isLeapYear(year))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    return 30;
}

//Count the days until day and month in a given year from January 1 of this year
int countDaysInYear(int year, int month, int day)
{
    int counter = 0;
    for(int i = month -1; i > 0; i--)
    {
        counter += getDays(i, year);
    }

    return counter + day;
}

//Count the Days from January 1, 1900 until the month day and year
int countDays(int year, int month, int day)
{
    int leapYears = countLeapYears(year);
    int yeardays = (year-leapYears-1900)*365 + leapYears * 366;

    return yeardays + countDaysInYear(year, month, day);
}

//Print the Name of the Day by the number of days since January 1, 1900 (which is a Monday)
void getNameByDays(int days)
{
    int mod = days % 7;
    if(mod == 1)
    {
        std::cout << "MONDAY";
    }
    else if( mod == 2)
    {
        std::cout << "TUESDAY";
    }
    else if (mod == 3)
    {
        std::cout << "WEDNESDAY";
    }
    else if (mod == 4)
    {
        std::cout << "THURSDAY";
    }
    else if (mod == 5)
    {
        std::cout << "FRIDAY";
    }
    else if(mod == 6)
    {
        std::cout << "SATURDAY";
    }
    else if(mod == 0)
    {
        std::cout << "SUNDAY";
    }
}

int main()
{
    std::cout << "Day? ";
    int day;
    std::cin >> day;

    std::cout << "Month? ";
    int month;
    std::cin >> month;

    std::cout << "Year? (>=1900)";
    int year;
    std::cin >> year;

    //Some asserts
    assert(year >= 1900);
    assert(day>0 && day < 32);
    assert(month>0 && month<13);

    //Count days since January, 1 1900
    std::cout << "Computed " << countDays(year, month, day) << " days since January 1, 1900" << std::endl;
    getNameByDays(countDays(year, month, day));


    return 0;
}
