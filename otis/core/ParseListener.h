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

#ifndef OTIS_PARSELISTENER_H
#define OTIS_PARSELISTENER_H

#include <string>
#include <vector>


namespace Otis {

    /**
     * The ParseListener is the listener interface to implement to get
     * notified about parsing events occurring while reading an input file.
     *
     * @version 0.1.0
     */
    class ParseListener {

    public:

        /**
         * Notifies this listener that parsing is going to start.
         * By default, this method does nothing.
         */
        virtual void startParse();

        /**
         * Notifies this listener about the metadata of the input instance.
         *
         * @param numberOfVariables The number of variables.
         * @param numberOfConstraints The number of constraints.
         */
        virtual void metaData(int numberOfVariables, int numberOfConstraints) = 0;

        /**
         * Notifies this listener that the objective function is going to be read.
         * By default, objective functions are not supported.
         */
        virtual void beginObjective();

        /**
         * Notifies this listener that a term of the objective function has been read.
         * By default, objective functions are not supported.
         *
         * @param coefficient The coefficient of the term.
         * @param literal The identifier of the literal.
         */
        virtual void objectiveTerm(long long coefficient, int literal);

        /**
         * Notifies this listener that a product of the objective function has been read.
         * By default, non-linear objective functions are not supported.
         *
         * @param coefficient The coefficient of the product.
         * @param literals The identifier of the literals which appear in the product.
         */
        virtual void objectiveProduct(long long coefficient, const std::vector<int> &literals);

        /**
         * Notifies this listener that the objective function has been fully read.
         * By default, objective functions are not supported.
         */
        virtual void endObjective();

        /**
         * Notifies this listener that a constraint is going to be read.
         */
        virtual void beginConstraint() = 0;

        /**
         * Notifies this listener that a term of a constraint has been read.
         *
         * @param coefficient The coefficient of the term.
         * @param literal The identifier of the literal.
         */
        virtual void constraintTerm(long long coefficient, int literal) = 0;

        /**
         * Notifies this listener that a product of a constraint has been read.
         * By default, non-linear constraints are not supported.
         *
         * @param coefficient The coefficient of the product.
         * @param literals The identifier of the literals which appear in the product.
         */
        virtual void constraintProduct(long long coefficient, const std::vector<int> &literals);

        /**
         * Notifies this listener that the relational operator of a constraint
         * has been read.
         *
         * @param relationalOperator The relational operator, which is one of
         *        "<", "<=", "=", ">=", ">".
         */
        virtual void constraintRelationalOperator(std::string relationalOperator) = 0;

        /**
         * Notifies this listener that the degree of a constraint has been read.
         *
         * @param degree The degree of the constraint.
         */
        virtual void constraintDegree(long long degree) = 0;

        /**
         * Notifies this listener that a constraint has been fully read.
         */
        virtual void endConstraint() = 0;

        /**
         * Notifies this listener that parsing is finished.
         * By default, this method does nothing.
         */
        virtual void endParse();

    };

}

#endif
