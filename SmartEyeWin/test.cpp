#include <string>
#include <vector>
#include <iostream>
#include "se_scan.h"

int main()
{
	std::vector<std::string>* window_list = window_scan();
	int i;
	int len = window_list->size();
	for (i = 0;i < len;i++)
	{
		std::cout << (*window_list)[i] << std::endl;
	}
	delete window_list;
	return 0;
}