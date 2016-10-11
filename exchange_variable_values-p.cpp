#include <iostream>

int main()
{
	int a, b;
	
	std::cin >> a >> b;
	
	int p = a;
	a = b;
	b = p;
	
	std::cout << a << " " << b << std::endl;
}
