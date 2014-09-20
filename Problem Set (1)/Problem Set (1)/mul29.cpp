#include <iostream>
#include "Header.h"

int problem12(){
	// read an integer a from the standart input
	int a;
	std::cin >> a;

	// Multiply 'a' with 29 without using any multiplication
	int i = 29;
	int b = 0;
	while (i != 0){
		i--;
		b += a;
	}
	std::cout << b << "\n";

	//Or only with additions:
	b = a;
	b += a;		// b = 2 * a
	b += b;		// b = 2 * b => b = 4 * a
	b += b;		// b = 8 * a
	b += b;		// b = 16 * a
	b += b;		// b = 32 * a
	b += (-a);	// b = 31 * a
	b += (-a);	// b = 30 * a
	b += (-a);	// b = 29 * a
	std::cout << b << "\n";

	std::cin >> a;
	return 0;
}