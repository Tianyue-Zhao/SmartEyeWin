/*#include <string>
#include <vector>
#include <iostream>
#include "se_scan.h"

//A test program that scans all currently active windows
int main()
{
	std::vector<std::string>* window_list = window_scan();
	int i;
	int len = window_list->size();
	std::cout << len << std::endl;
	for (i = 0;i < len;i++)
	{
		if (!(*window_list)[i].length()) { continue; }
		std::cout << (*window_list)[i] << std::endl;
	}
	delete window_list;
	return 0;
}*/