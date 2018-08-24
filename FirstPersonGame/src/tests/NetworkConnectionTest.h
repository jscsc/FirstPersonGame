#pragma once
#include "TestBase.h"
class NetworkConnectionTest : public TestBase
{
public:

	NetworkConnectionTest(){}
	~NetworkConnectionTest(){}

	virtual bool run()
	{
		AutoLogger logger(_passedTest, "network connection");

		//startup two tcp connections

		//make one listen

		//have one connect

		//have A send msg to B

		//assert that msg == sent

		//have B send msg to A

		//assert msg == sent

		return _passedTest;
	}

};

