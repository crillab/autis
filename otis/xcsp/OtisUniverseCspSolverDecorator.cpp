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

    OtisUniverseCspSolverDecorator::OtisUniverseCspSolverDecorator(Universe::IUniverseCspSolver *solver, FILE *in)
            : solver(solver), in(in) {}

    void OtisUniverseCspSolverDecorator::parse() {
        OtisXcspCallback cb(solver);
        XCSP3Core::XCSP3CoreParser parser(&cb);
        parser.parse(in);
    }


} // Otis