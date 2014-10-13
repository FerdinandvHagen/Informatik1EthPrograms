#include <iostream>

int main(void){
	for (int b = 0; b < 10; b++){
		for (int a = 0; a < b; a++){
			std::cout << a*b << std::endl;
		}
	}

	int b;
	std::cin >> b;
	return 0;
}