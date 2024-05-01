#include <iostream>
#include "../header/vector.hpp"
#include "../header/myallocator.h"

int main()
{
	Vector<int, MyAllocator<int>> vec(5, 10);
	std::cout << vec;
	Vector<int, MyAllocator<int>> vec2;
	vec2.print();
	std::cout << std::endl;
	vec2.push_back(4);
	vec2.push_back(1);
	vec2.push_back(3);
	vec2.push_back(5);
	vec2.push_back(2);
	vec2.push_back(6);
	vec2.push_back(7);
	vec2.push_back(8);
	vec2.push_back(9);
	vec2.print();
//	std::cout << vec.Vcap() << std::endl;
//	vec.shrink_to_fit();
//	std::cout << vec.Vcap() << std::endl;
}
