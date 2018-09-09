#include "GameManager.h"

#ifdef RUN_TESTS
#include "./tests/TestLauncher.h"
#endif //RUN_TESTS


int main()
{
#ifdef RUN_TESTS
	TestLauncher test_suite;
	test_suite.launchTests();
#else // !RUN_TESTS
	GameManager gameManager;
	gameManager.gameLoop();
#endif // RUN_TESTS

	return 0;
}