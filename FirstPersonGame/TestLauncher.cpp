#include "TestLauncher.h"
#include <iostream>



TestLauncher::TestLauncher()
{
}


TestLauncher::~TestLauncher()
{
}

void TestLauncher::launchTests()
{
	int passingTests = 0;
	int totalTests = 0;

	std::cout << "passes " << passingTests << " out of " << totalTests << std::endl;

	std::cout << "Press enter to close" << std::endl;
	std::cin.get();
}
