//
// Created by Oliver Zhang on 2021-04-02.
//

#include "catch.hpp"
#include <cmath>
#include "quadratic_solver.h"

TEST_CASE("Quadratic solver") {
    SECTION("solveEarliestSolution") {
        SECTION("wide bound") {
            Bound1d bound = Bound1d(-100000, 100000);
            SECTION("no solution") {
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(1, 0, 1, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(0.01, 0, 1, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(10, 0, 1, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(1, 0, 0.0001, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(1, 1.999, 1, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(1, -1.999, 1, bound)));

                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(-1, 0, -1, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(-0.01, 0, -1, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(-10, 0, -1, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(-1, 0, -0.0001, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(-1, 1.999, -1, bound)));
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(-1, -1.999, -1, bound)));
            }

            SECTION("1 solution") {
                REQUIRE(QuadraticSolver::solveEarliestSolution(1, std::sqrt(4 * 1 * 0), 0, bound) == 0);
                REQUIRE(QuadraticSolver::solveEarliestSolution(1, std::sqrt(4 * 1 * 10), 10, bound) ==
                        Approx(-0.5 * std::sqrt(4 * 1 * 10)));
            }

            SECTION("2 solutions") {
                REQUIRE(QuadraticSolver::solveEarliestSolution(1, 0, -1, bound) == -1);
                REQUIRE(QuadraticSolver::solveEarliestSolution(-1, 0, 1, bound) == -1);
                REQUIRE(QuadraticSolver::solveEarliestSolution(16, 0, -1, bound) == -0.25);
                REQUIRE(QuadraticSolver::solveEarliestSolution(-16, 0, 1, bound) == -0.25);
                REQUIRE(QuadraticSolver::solveEarliestSolution(1, 1, 0, bound) == -1);
                REQUIRE(QuadraticSolver::solveEarliestSolution(7, 5, -1, bound) == Approx(-0.8771507064));
                REQUIRE(QuadraticSolver::solveEarliestSolution(11, -5, 0.5, bound) == Approx(0.1485431451));
            }
        }

        SECTION("narrow bound") {
            Bound1d bound = Bound1d(-100000, 100000);

            SECTION("1 solution out of bound") {
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(1, std::sqrt(4 * 1 * 0), 0, Bound1d(1, 2))));
            }

            SECTION("2 solutions all out of bound") {
                REQUIRE(std::isnan(QuadraticSolver::solveEarliestSolution(1, 0, -1, Bound1d(1, 2))));
            }

            SECTION("2 solutions 1 in bound") {
                REQUIRE(QuadraticSolver::solveEarliestSolution(1, 0, -1, Bound1d(-1.5, -0.5)) == -1);
            }
        }
    }
}
