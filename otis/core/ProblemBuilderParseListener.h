/******************************************************************************
 * OTIS - Opening wriTing and readIng instanceS                               *
 * Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.                   *
 * All rights reserved.                                                       *
 *                                                                            *
 * This library is free software; you can redistribute it andor               *
 * modify it under the terms of the GNU Lesser General Public                 *
 * License as published by the Free Software Foundation; either               *
 * version 3 of the License, or (at your option) any later version.           *
 *                                                                            *
 * This library is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with this library.                                           *
 * If not, see {@link http:www.gnu.orglicenses}.                              *
 ******************************************************************************/

#ifndef OTIS_PROBLEMBUILDERPARSELISTENER_H
#define OTIS_PROBLEMBUILDERPARSELISTENER_H

#include <memory>
#include <string>
#include <vector>

#include "ParseListener.h"


namespace Otis {

    /**
     * The ProblemBuilderParseListener is a listener that allows to build a CNF or a
     * pseudo-Boolean problem that is read from an input stream.
     *
     * @version 0.1.0
     */
    class ProblemBuilderParseListener : public Otis::ParseListener {

    private:

        /**
         * The number of variables of the read problem.
         */
        int numberOfVariables;

        /**
         * The constraints of the read problem.
         */
        std::vector<std::shared_ptr<Otis::Constraint>> constraints;

        /**
         * The literals of the current constraint.
         */
        std::vector<int> literals;

        /**
         * The coefficients of the current constraint.
         */
        std::vector<long long> coefficients;

        /**
         * The relational operator of the current constraint.
         */
        std::string relationalOperator;

        /**
         * The degree of the current constraint.
         */
        long long degree;

        /**
         * Whether all the coefficients of the current constraint are equal to 1.
         */
        bool allCoefficientsAre1;



    public:

        /**
         * Creates a new ProblemBuilderParseListener.
         */
        explicit ProblemBuilderParseListener();

        /**
         * Initializes the internal data structures of this listener to handle
         * the given number of variables and the given number of constraints.
         *
         * @param nbVariables The number of variables.
         * @param nbConstraints The number of constraints.
         */
        void metaData(int nbVariables, int nbConstraints) override;

        /**
         * Sets up the internal data structures to prepare the reading of a new
         * constraint.
         */
        void beginConstraint() override;

        /**
         * Adds a term to the constraint that is being built.
         *
         * @param coefficient The coefficient of the term.
         * @param literal The literal of the term.
         */
        void constraintTerm(long long coefficient, int literal) override;

        /**
         * Sets the relational operator of the constraint that is being built.
         *
         * @param relationalOperator The relational operator, which is one of
         *        "<", "<=", "=", ">=", ">".
         */
        void constraintRelationalOperator(std::string relationalOperator) override;

        /**
         * Sets the degree of the constraint that is being built.
         *
         * @param degree The degree of the constraint.
         */
        void constraintDegree(long long degree) override;

        /**
         * Instantiates the constraint that is currently being built.
         */
        void endConstraint() override;

        /**
         * Builds the problem that has been read.
         *
         * @return The read problem.
         */
        [[nodiscard]] std::shared_ptr<Otis::Problem> buildProblem();

    };

}

#endif
