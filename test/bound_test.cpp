//
// Created by Oliver Zhang on 2021-04-02.
//

#include "catch.hpp"
#include "bound.h"

TEST_CASE("Bound") {
    SECTION("Bound1") {
        Bound1d b1(0, 1);
        Bound1d b2(-10, 20);

        REQUIRE(b1.contains(3.5) == false);
        REQUIRE(b1.contains(0.2) == true);
        REQUIRE(b2.contains(0) == true);
        REQUIRE(b2.contains(-10.001) == false);
        REQUIRE(b2.contains(20.0001) == false);
        REQUIRE(b2.contains(1000) == false);
    }

    SECTION("Bound3") {
        Bound3d unitCube({0, 0, 0}, {1, 1, 1});

        REQUIRE(unitCube.hitRay(Ray3d({0, 0, 0}, {1, 1, 1}), -infinity, infinity) == true);
        REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 5}, {0, 0, -1}), -infinity, infinity) == true);
        REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 5}, {0.01, 0.01, -1}), -infinity, infinity) == true);
        REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 5}, {-0.01, -0.01, -1}), -infinity, infinity) == true);

        SECTION("ray originates inside bound") {
            REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 0.5}, {0.0, 0.0, 0.1}), 0, infinity) == true);
            REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 0.5}, {0.0, 0.1, 0.0}), 0, infinity) == true);
            REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 0.5}, {0.0, 0.1, 0.1}), 0, infinity) == true);
            REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 0.5}, {0.1, 0.0, 0.0}), 0, infinity) == true);
            REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 0.5}, {0.1, 0.0, 0.1}), 0, infinity) == true);
            REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 0.5}, {0.1, 0.1, 0.0}), 0, infinity) == true);
            REQUIRE(unitCube.hitRay(Ray3d({0.5, 0.5, 0.5}, {0.1, 0.1, 0.1}), 0, infinity) == true);
        }
    }
}
