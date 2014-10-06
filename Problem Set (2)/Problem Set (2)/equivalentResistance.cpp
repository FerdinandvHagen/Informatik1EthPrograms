#include <iostream>

int main(void){
	int r1;
	int r2;
	int r3;
	int r4;

	std::cout << "Enter values for R1, R2, R3 and R4:" << std::endl;
	std::cin >> r1 >> r2 >> r3 >> r4;


	// Compute the serial resistance of each branch
	int r12 = r1 + r2;
	int r34 = r3 + r4;


	/*
	This would result in a "division by zero" exception:

	int rg = 1 / ((1 / r12) + (1 / r34));
	*/

	//So correct would be:
	int rg = r12 * r34 / (r12 + r34);
	std::cout << "The correct equivalent resistance is " << rg << "Ohm" << std::endl;

	return 0;
}