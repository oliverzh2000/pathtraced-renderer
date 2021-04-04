//
// Created by Oliver Zhang on 2021-04-02.
//

#include "catch.hpp"
#include "geometry.h"
#include <cmath>

TEST_CASE("Geometry", "[Vector3d basics]" ) {
    Vector3d v0(0, 0, 0);
    Vector3d v1(1, 1, 1);
    Vector3d v1x(1, 0, 0);
    Vector3d v1y(0, 1, 0);
    Vector3d v1z(0, 0, 1);
    Vector3d v2 = Vector3d(5, 6, 7);

    SECTION("add, sub, scalar mul/div") {
        REQUIRE(2.0 * v1x + 3.0 * v1y + 4.0 * v1z == Vector3d(2, 3, 4));
        REQUIRE(0.1 * v1x + 0.2 * v1y + 0.3 * v1z == Vector3d(0.1, 0.2, 0.3));
        REQUIRE(v1x / 10 + v1y / 5 + v1z / 4 == Vector3d(0.1, 0.2, 0.25));
        REQUIRE(v0 - v1x - v1y - v1z == Vector3d(-1, -1, -1));
        REQUIRE(-v2 == Vector3d(-5, -6, -7));
    }

    SECTION("add, sub, scalar mul/div in place") {
        v1 += v1x;
        v1 += v1y;
        v1 += v1z;
        REQUIRE(v1 == Vector3d(2, 2, 2));
        v1 -= v1x;
        v1 -= v1y;
        v1 -= v1z;
        REQUIRE(v1 == Vector3d(1, 1, 1));
    }

    SECTION("equality") {
        REQUIRE(v0 != v1x);
        REQUIRE(v0 != v1y);
        REQUIRE(v0 != v1z);

        REQUIRE(v0 == v0);
        REQUIRE(v1x == v1x);
        REQUIRE(v1y == v1y);
        REQUIRE(v1z == v1z);
    }

    SECTION("length, normalization") {
        REQUIRE(v0.length() == 0);
        REQUIRE(v0.lengthSquared() == 0);
        REQUIRE(v1x.length() == 1.0);
        REQUIRE(v1y.length() == 1.0);
        REQUIRE(v1z.length() == 1.0);

        REQUIRE(v1.length() == std::sqrt(3.0));
        REQUIRE(v1.lengthSquared() == 3.0);

        REQUIRE(Vector3d(3, 4, 5).lengthSquared() == 3 * 3 + 4 * 4 + 5 * 5);

        REQUIRE(v1x.normalized() == v1x);
        REQUIRE(v1y.normalized() == v1y);
        REQUIRE(v1z.normalized() == v1z);
        REQUIRE(v2.normalized() == v2 / v2.length());
    }

    SECTION("dot product") {
        REQUIRE(v0.dot(v1) == 0);
        REQUIRE(v0.dot(v1x) == 0);
        REQUIRE(v0.dot(v1y) == 0);
        REQUIRE(v0.dot(v1z) == 0);

        REQUIRE(v1x.dot(v1x) == 1);
        REQUIRE(v1y.dot(v1y) == 1);
        REQUIRE(v1z.dot(v1z) == 1);

        REQUIRE(Vector3d(1, 10, 100).dot(Vector3d(2, 3, 4)) == 432);
        REQUIRE(Vector3d(-1, -10, -100).dot(Vector3d(-2, -3, -4)) == 432);
        REQUIRE(Vector3d(-1, -10, -100).dot(Vector3d(2, 3, 4)) == -432);

        REQUIRE(v2.dot(v2) == v2.lengthSquared());
    }

    SECTION("cross product") {
        SECTION("right-handedness") {
            REQUIRE(v1x.cross(v1y) == v1z);
            REQUIRE(v1y.cross(v1z) == v1x);
            REQUIRE(v1z.cross(v1x) == v1y);
        }

        REQUIRE(Vector3d(-3, 1, -2).cross(Vector3d(5, -1, 2)) == Vector3d(0, -4, -2));
    }
}
