#pragma once
#include <vector>
#include "TestBase.h"
#include "..\utilities\smart_ptr_typedefs.h"
class TestLauncher
{
private:
	std::vector < sp<TestBase> > _tests;

protected:
	void GenerateTests();
public:

	TestLauncher();

	~TestLauncher();

	void launchTests();
};

