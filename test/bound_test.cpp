//
// Created by Oliver Zhang on 2021-04-02.
//

#include "catch.hpp"
#include "bound.h"

TEST_CASE("Bound") {
    Bound1d b1(0, 1);
    Bound1d b2(-10, 20);

    REQUIRE(b1.contains(3.5) == false);
    REQUIRE(b1.contains(0.2) == true);
    REQUIRE(b2.contains(0) == true);
    REQUIRE(b2.contains(-10.001) == false);
    REQUIRE(b2.contains(20.0001) == false);
    REQUIRE(b2.contains(1000) == false);
}
