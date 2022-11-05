/******************************************************************************
 * AUTIS, a library for parsing combinatorial problems.                       *
 * Copyright (c) 2022 - Exakis Nelite, Univ Artois & CNRS.                    *
 * All rights reserved.                                                       *
 *                                                                            *
 * This library is free software; you can redistribute it andor               *
 * modify it under the terms of the GNU Lesser General Public                 *
 * License as published by the Free Software Foundation; either               *
 * version 3 of the License, or (at your option) any later version.         *
 *                                                                            *
 * This library is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with this library.                                           *
 * If not, see http//:www.gnu.org/licenses.                                   *
 ******************************************************************************/

/**
* @file AutisUniverseCspSolverDecorator.cpp
* @brief
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
*/


#include "AutisUniverseCspSolverDecorator.hpp"
#include "AutisXcspCallback.hpp"
#include "XCSP3CoreParser.h"

namespace Autis {

    AutisUniverseCspSolverDecorator::AutisUniverseCspSolverDecorator(Universe::IUniverseSolver *solver, FILE *in)
            : solver(solver), in(in) {}

    void AutisUniverseCspSolverDecorator::parse() {
        AutisXcspCallback cb(dynamic_cast<Universe::IUniverseCspSolver*>(solver));
        XCSP3Core::XCSP3CoreParser parser(&cb);
        cb.recognizeSpecialIntensionCases=false;
        parser.parse(in);
    }

    Universe::UniverseSolverResult AutisUniverseCspSolverDecorator::solve() {
        return solver->solve();
    }

    Universe::UniverseSolverResult AutisUniverseCspSolverDecorator::solve(std::string filename) {
        return Universe::UniverseSolverResult::OPTIMUM_FOUND;
    }

    void AutisUniverseCspSolverDecorator::interrupt() {

    }

    void AutisUniverseCspSolverDecorator::setVerbosity(int level) {

    }

    void AutisUniverseCspSolverDecorator::setTimeout(long seconds) {

    }

    void AutisUniverseCspSolverDecorator::setTimeoutMs(long mseconds) {

    }

    void AutisUniverseCspSolverDecorator::reset() {

    }

    int AutisUniverseCspSolverDecorator::nVariables() {
        return 0;
    }

    int AutisUniverseCspSolverDecorator::nConstraints() {
        return 0;
    }

    void AutisUniverseCspSolverDecorator::setLogFile(const string &filename) {

    }

    vector<Universe::BigInteger> AutisUniverseCspSolverDecorator::AutisUniverseCspSolverDecorator::solution() {
        return {};
    }

    Universe::UniverseSolverResult AutisUniverseCspSolverDecorator::solve(std::vector<Universe::UniverseAssumption<Universe::BigInteger>> assumpts){
        return Universe::UniverseSolverResult::UNKNOWN;
    }


} // Autis