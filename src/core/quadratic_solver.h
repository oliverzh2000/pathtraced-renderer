//
// Created by Oliver Zhang on 2021-03-28.
//

#ifndef PATHTRACED_RENDERER_QUADRATIC_SOLVER_H
#define PATHTRACED_RENDERER_QUADRATIC_SOLVER_H


/*
 * Utility function to find (Real valued) solutions to a quadratic equation.
 *
 * Uses an alternate (but equivalent assuming exact arithmetic) formula for one of the roots depending on
 * the sign of b, to prevent potential loss of precision from subtracting 2 large and nearly equal numbers.
 */
#include <utility>
#include <cmath>

#include "bound.h"

namespace QuadraticSolver {
    /*
     * Return the (real) roots of the equation a^2t + b^t + c = 0.
     * If there are no solutions, then return a pair of NaNs.
     * If there is only 1 solution, then the 2nd element of the solution is NaN.
     * It is guaranteed that 1st element of solution < 2nd element of solution (provided they exist).
     */
    inline std::pair<double, double> solve(double a, double b, double c) {
        double discr = b * b - 4 * a * c;
        if (discr < 0) {
            return std::make_pair(NAN, NAN);
        } else if (discr == 0) {
            return std::make_pair(-b / (2 * a), NAN);
        } else {
            double sqrtDiscr = std::sqrt(discr);
            // Subtracting 2 large floats is avoided using this alternate formula.
//            double temp = -0.5 * (b + static_cast<int>(std::signbit(b))) * sqrtDiscr;
//            return std::make_pair(temp / a, c / temp);
            if (b > 0) {
                return std::make_pair((-b - sqrtDiscr) / (2 * a), 2 * c / (-b - sqrtDiscr));
            } else {
                return std::make_pair(2 * c / (-b + sqrtDiscr), (-b + sqrtDiscr) / (2 * a));
            }
        }
    }

    /*
     * Return the smallest (real) root of the equation a^2t + b^t + c = 0.
     * If there is no solution in the range, return NaN.
     */
    inline double solveEarliestSolution(double a, double b, double c, Bound1d solutionRange) {
        double discr = b * b - 4 * a * c;
        if (discr < 0) {
            return NAN;
        } else if (discr == 0) {
            double solution = -b / (2 * a);
            return solutionRange.contains(solution) ? solution : NAN;
        } else {
            double sqrtDiscr = std::sqrt(discr);
            // Subtracting 2 large floats is avoided using this alternate formula.
            double bSign = b > 0 ? 1 : -1;
            double temp = -0.5 * (b +  bSign * sqrtDiscr);
            double soln1 = temp / a;
            double soln2 = c / temp;
            double solnMin = std::min(soln1, soln2);
            double solnMax = std::max(soln1, soln2);
            if (solutionRange.contains(solnMin)) {
                return solnMin;
            } else if (solutionRange.contains(solnMax)) {
                return solnMax;
            } else {
                return NAN;
            }
        }
    }
};


#endif //PATHTRACED_RENDERER_QUADRATIC_SOLVER_H
