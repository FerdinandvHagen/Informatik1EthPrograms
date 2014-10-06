#include <iostream>

void recdec2bin(int n);

int main(void){
	std::cout << "Please input an integer: ";
	unsigned int n;
	std::cin >> n;

	recdec2bin(n);
	std::cout << std::endl;

	std::cin >> n;
	return 0;
}

void recdec2bin(int n){
	if (n != 0){
		recdec2bin(n / 2);
		std::cout << n % 2;
	}
}