#include <iostream>
#include "Header.h"

/*
Müsste man das Problem per Hand auf dem Papier lösen, würde ich einfach 29 mal die Zahl addieren.
Oder wie bei der zweiten Lösung angegeben, würde ich die Zahl einfach bis 32 verfielfachen und das Ergebnis wieder um 3 * den Input reduzieren
*/

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
