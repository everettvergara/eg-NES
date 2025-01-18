#define CATCH_CONFIG_RUNNER  // This allows us to define a custom main()
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>  // Required for Catch::Session
#include <iostream>
#include <stdexcept>  // For std::invalid_argument

// Calculator class
class Calculator {
public:
	int add(int a, int b) const { return a + b; }
	int subtract(int a, int b) const { return a - b; }
	int multiply(int a, int b) const { return a * b; }
	int divide(int a, int b) const {
		if (b == 0) throw std::invalid_argument("Division by zero");
		return a / b;
	}
};

// Test cases
TEST_CASE("Calculator operations", "[Calculator]") {
	Calculator calc;

	SECTION("Addition") {
		REQUIRE(calc.add(3, 2) == 5);
		REQUIRE(calc.add(-1, 1) == 0);
	}

	SECTION("Subtraction") {
		REQUIRE(calc.subtract(5, 3) == 2);
		REQUIRE(calc.subtract(0, 10) == -10);
	}

	SECTION("Multiplication") {
		REQUIRE(calc.multiply(4, 3) == 12);
		REQUIRE(calc.multiply(7, 0) == 0);
	}

	SECTION("Division") {
		REQUIRE(calc.divide(6, 2) == 3);
		REQUIRE_THROWS_AS(calc.divide(5, 0), std::invalid_argument);
	}
}

// Custom main() function
int main(int argc, char* argv[]) {
	// Custom setup code (if needed)
	std::cout << "Starting Catch2 tests...\n";

	// Run the Catch2 session
	int result = Catch::Session().run(argc, argv);

	// Custom teardown code (if needed)
	std::cout << "All tests completed.\n";

	// Return the result of the Catch2 tests
	return result;
}
