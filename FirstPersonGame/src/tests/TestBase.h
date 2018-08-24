#pragma once

#include <iostream>
#include <string>

struct AutoLogger
{
	bool& _passedTest;
	std::string testName;
	
	AutoLogger(bool& passing, std::string testName) : _passedTest(passing)
	{
		std::cout << "TEST: " << testName << "\t ";
	}
	~AutoLogger()
	{
		std::cout << " STATUS: [" << ((_passedTest) ? "passed" : "failed") << "]" << std::endl;
	}
};

class TestBase
{
public:
	TestBase();
	virtual ~TestBase();

protected:
	bool _passedTest = true;

public:
	virtual bool run() = 0;
};

