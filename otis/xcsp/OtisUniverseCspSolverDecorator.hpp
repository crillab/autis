/**
* @file OtisUniverseCspSolverDecorator.hpp
* @brief
* @author Thibault Falque
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
*/


#ifndef OTIS_OTISUNIVERSECSPSOLVERDECORATOR_HPP
#define OTIS_OTISUNIVERSECSPSOLVERDECORATOR_HPP

#include "../../libs/universe/universe/include/csp/IUniverseCspSolver.hpp"

namespace Otis {

/**
* @class OtisUniverseCspSolverDecorator
* @brief 
*/
    class OtisUniverseCspSolverDecorator:public Universe::IUniverseSolver {
    public:
        OtisUniverseCspSolverDecorator(Universe::IUniverseSolver *solver, FILE *in);

        ~OtisUniverseCspSolverDecorator() override =default ;

        void parse();
    private:
        Universe::IUniverseSolver* solver;
        FILE* in;
    };

} // Otis

#endif //OTIS_OTISUNIVERSECSPSOLVERDECORATOR_HPP
