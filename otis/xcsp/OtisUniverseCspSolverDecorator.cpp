/**
* @file OtisUniverseCspSolverDecorator.cpp
* @brief
* @author Thibault Falque
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
*/


#include "OtisUniverseCspSolverDecorator.hpp"
#include "OtisXcspCallback.hpp"
#include "XCSP3CoreParser.h"

namespace Otis {

    OtisUniverseCspSolverDecorator::OtisUniverseCspSolverDecorator(Universe::IUniverseSolver *solver, FILE *in)
            : solver(solver), in(in) {}

    void OtisUniverseCspSolverDecorator::parse() {
        OtisXcspCallback cb(dynamic_cast<Universe::IUniverseCspSolver*>(solver));
        XCSP3Core::XCSP3CoreParser parser(&cb);
        parser.parse(in);
    }

    Universe::UniverseSolverResult OtisUniverseCspSolverDecorator::solve() {
        return Universe::UniverseSolverResult::OPTIMUM_FOUND;
    }

    Universe::UniverseSolverResult OtisUniverseCspSolverDecorator::solve(std::string filename) {
        return Universe::UniverseSolverResult::OPTIMUM_FOUND;
    }

    void OtisUniverseCspSolverDecorator::interrupt() {

    }

    void OtisUniverseCspSolverDecorator::setVerbosity(int level) {

    }

    void OtisUniverseCspSolverDecorator::setTimeout(long seconds) {

    }

    void OtisUniverseCspSolverDecorator::setTimeoutMs(long mseconds) {

    }

    void OtisUniverseCspSolverDecorator::reset() {

    }

    int OtisUniverseCspSolverDecorator::nVariables() {
        return 0;
    }

    int OtisUniverseCspSolverDecorator::nConstraints() {
        return 0;
    }

    void OtisUniverseCspSolverDecorator::setLogFile(const string &filename) {

    }

    vector<Universe::BigInteger> OtisUniverseCspSolverDecorator::OtisUniverseCspSolverDecorator::solution() {
        return {};
    }

    Universe::UniverseSolverResult OtisUniverseCspSolverDecorator::solve(std::vector<Universe::UniverseAssumption<Universe::BigInteger>> assumpts){
        return Universe::UniverseSolverResult::UNKNOWN;
    }


} // Otis