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

} // Otis

#endif //OTIS_OTISUNIVERSECSPSOLVERDECORATOR_HPP
