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
* @file AutisUniverseCspSolverDecorator.hpp
* @brief
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
*/


#ifndef AUTIS_AUTISUNIVERSECSPSOLVERDECORATOR_HPP
#define AUTIS_AUTISUNIVERSECSPSOLVERDECORATOR_HPP

#include "../../libs/universe/universe/include/csp/IUniverseCspSolver.hpp"

namespace Autis {

/**
* @class AutisUniverseCspSolverDecorator
* @brief 
*/
    class AutisUniverseCspSolverDecorator: public Universe::IUniverseSolver {
    public:
        AutisUniverseCspSolverDecorator(Universe::IUniverseSolver *solver, FILE *in);

        ~AutisUniverseCspSolverDecorator() override =default ;

        void parse();

        Universe::UniverseSolverResult solve() override;

        Universe::UniverseSolverResult solve(std::string filename) override;
        Universe::UniverseSolverResult solve(std::vector<Universe::UniverseAssumption<Universe::BigInteger>> assumpts) override;

        void interrupt() override;

        void setVerbosity(int level) override;

        void setTimeout(long seconds) override;

        void setTimeoutMs(long mseconds) override;

        void reset() override;

        int nVariables() override;

        int nConstraints() override;

        void setLogFile(const std::string &filename) override;

        std::vector<Universe::BigInteger> solution() override;



    private:
        Universe::IUniverseSolver* solver;
        FILE* in;
    };

} // Autis

#endif //AUTIS_AUTISUNIVERSECSPSOLVERDECORATOR_HPP
