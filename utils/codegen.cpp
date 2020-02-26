#include <iostream>
#include <string>

int main()
{
	std::string result;
	std::string str;
	while(std::getline(std::cin, str))
	{
		result += str;
	}
	
	std::cout << "MakeCharArray<";
	for(size_t i = 0; i < result.size(); ++i)
	{
		if(i > 0)
			std::cout << ", ";
		std::cout << "\'" << result[i] << "\'";
	}
	std::cout << ", \'\\0\'>";
	return 0;
}