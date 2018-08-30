#include "TestLauncher.h"
#include <iostream>
#include "..\utilities\smart_ptr_typedefs.h"
#include "NetworkConnectionTest.h"
#include "NetworkManagerConnectTest.h"

void TestLauncher::GenerateTests()
{
	_tests = 
	{ 
		new_sp<NetworkConnectionTest>(),
		new_sp<NetworkManagerConnectTest>() 

	};
}

TestLauncher::TestLauncher()
{

}

TestLauncher::~TestLauncher()
{
}

void TestLauncher::launchTests()
{
	GenerateTests();

	int passingTests = 0;
	int totalTests = 0;

	for (auto& test : _tests)
	{
		passingTests += test->run();
		totalTests++;
	}

	std::cout << "passes " << passingTests << " out of " << totalTests << std::endl;

	std::cout << "Press enter to close" << std::endl;
	std::cin.get();
}
