#include "CppUTest/TestHarness.h"

extern "C" {
	#include "hertz.h"
}

TEST_GROUP(functionalTests) {
	void setup() {
		// runs before each test
	}

	void teardown() {
		//runs after each test
	}
};

Test(functionalTests, Test_testHarness) {
	LONGS_EQUAL(7, 6);
}
