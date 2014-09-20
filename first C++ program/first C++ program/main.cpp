#include <iostream>

int main(){
	// input
	std::cout << "Compute a^8 for a =? ";

	int a;
	std::cin >> a;

	// computation
	int b = a * a;		// b = a^2
	b = b * b;			// b = a^4

	// output b * b, i.e., a^8
	std::cout << a << "^8 = " << b*b << ".\n";

	return 0;
}