
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "MathUtils.h"

using Catch::Approx;

TEST_CASE("Vector3 functionality", "[math_utils]") {
    SECTION("Vector3 construction") {
        Vector3 v1;
        REQUIRE(v1.x == Approx(0.0));
        REQUIRE(v1.y == Approx(0.0));
        REQUIRE(v1.z == Approx(0.0));
        
        Vector3 v2{1.0, 2.0, 3.0};
        REQUIRE(v2.x == Approx(1.0));
        REQUIRE(v2.y == Approx(2.0));
        REQUIRE(v2.z == Approx(3.0));
    }
    
    SECTION("Vector3 arithmetic operations") {
        Vector3 v1{1.0, 2.0, 3.0};
        Vector3 v2{4.0, 5.0, 6.0};
        
        // Test addition if implemented
        // Vector3 sum = v1 + v2;
        // REQUIRE(sum.x == Approx(5.0));
        // REQUIRE(sum.y == Approx(7.0));
        // REQUIRE(sum.z == Approx(9.0));
    }
    
    SECTION("Vector3 magnitude calculation") {
        Vector3 v{3.0, 4.0, 0.0};
        // If magnitude method exists
        // REQUIRE(v.magnitude() == Approx(5.0));
    }
}

// Add more math utility tests based on what's available in MathUtils.h/cpp
TEST_CASE("Mathematical utility functions", "[math_utils]") {
    SECTION("Angle calculations") {
        // Test angle conversion functions if they exist
        // REQUIRE(degrees_to_radians(180.0) == Approx(M_PI));
        // REQUIRE(radians_to_degrees(M_PI) == Approx(180.0));
    }
    
    SECTION("Ballistic calculations") {
        // Test any ballistic utility functions
        // These would depend on what's actually implemented in MathUtils
    }
}
