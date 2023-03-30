#include <catch2/catch_test_macros.hpp>
#include "../src/engine/graphics/renderable/bounds.h"

using namespace spright::engine;

TEST_CASE("Bounds", "[bounds]") {
	SECTION("can check if it contains a coordinate") {
		Bounds bounds(2, -2, 5, 5);

		REQUIRE(bounds.contains(1.9f, 0) == false);
		REQUIRE(bounds.contains(7.1f, 0) == false);
		REQUIRE(bounds.contains(0, -2.1f) == false);
		REQUIRE(bounds.contains(0, 3.1f) == false);

		REQUIRE(bounds.contains(2.1f, 0) == true);
		REQUIRE(bounds.contains(6.9f, 0) == true);
		REQUIRE(bounds.contains(3, -1.9f) == true);
		REQUIRE(bounds.contains(3, 2.9f) == true);
	}
}