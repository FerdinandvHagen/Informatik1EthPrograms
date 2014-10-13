#include <iostream>
#include <cassert>

void recdec2bin(int n);
void problem34(void);
void problem34b(void);
bool isPrime(int n);
int main(void){
	std::cout << "Please input an integer: ";
	unsigned int n;
	std::cin >> n;

	recdec2bin(n);
	std::cout << std::endl;

	problem34();

	problem34b();

	std::cout << std::endl << std::endl << "Primes until overflow";

	std::cin >> n;
	return 0;
}

void recdec2bin(int n){
	if (n != 0){
		recdec2bin(n / 2);
		std::cout << n % 2;
	}
}

void problem34(void){
	std::cout << "Please enter a number: ";
	int n;
	std::cin >> n;

	int left = 0;
	int right = 1;

	std::cout << "0" << std::endl;
	while (right <= n){
		if (isPrime(right)){
			std::cout << right << std::endl;
		}
		int res = left + right;
		left = right;
		right = res;
	}
}

void problem34b(void){
	unsigned long left = 0u;
	unsigned long right = 1u;
	std::cout << "0" << std::endl;
	while (right >= left){
		if (isPrime(right)){
			std::cout << right << std::endl;
		}
		int res = left + right;
		left = right;
		right = res;
	}
	std::cout << "problem 3.4 b solved: overflow after fibonacci prime " << left << " because the next value was " << right << std::endl;
	assert(right < left);
}

bool isPrime(int n){
	if (n <= 1){
		return false;
	}
	unsigned int d;
	for (d = 2; n % d != 0; ++d);

	if (d < n){
		//d is a divisor of n in {2, ..., n-1}
		return false;
	}
	else {
		assert(d == n);
		//there is no d in {2, ..., n-1} to divide n
		return true;
	}
}