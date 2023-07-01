/******************************************************************************
 * AUTIS, A Unified Tool for parsIng problemS                                 *
 * Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.                   *
 * All rights reserved.                                                       *
 *                                                                            *
 * This library is free software; you can redistribute it and/or modify it    *
 * under the terms of the GNU Lesser General Public License as published by   *
 * the Free Software Foundation; either version 3 of the License, or (at your *
 * option) any later version.                                                 *
 *                                                                            *
 * This library is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.                                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with this library.                                           *
 * If not, see http://www.gnu.org/licenses.                                   *
 ******************************************************************************/

/**
 * @file AbstractParser.hpp
 * @brief Defines the base class for all parsers implemented in Autis.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef AUTIS_ABSTRACTPARSER_HPP
#define AUTIS_ABSTRACTPARSER_HPP

#include <crillab-universe/core/IUniverseSolver.hpp>

#include "Scanner.hpp"

namespace Autis {

    /**
     * The AbstractParser is the parent class of classes used to parse input streams
     * so as to read a problem to solve.
     */
    class AbstractParser {

    protected:

        /**
         * The scanner used to read the input stream.
         */
        Autis::Scanner &scanner;

        /**
         * The solver to feed while parsing.
         */
        Universe::IUniverseSolver* solver;

        /**
         * The number of variables in the problem that is being read.
         */
        int numberOfVariables;

        /**
         * The number of constraints in the problem that is being read.
         */
        int numberOfConstraints;

    protected:

        /**
         * Creates a new AbstractParser.
         *
         * @param scanner The scanner used to read the input stream.
         * @param solver The solver to feed while parsing the instance.
         */
        explicit AbstractParser(Autis::Scanner &scanner, Universe::IUniverseSolver* solver);

    public:

        /**
         * Destroys this AbstractParser.
         */
        virtual ~AbstractParser() = default;

        virtual bool isOptimization();

        /**
         * Parses the input to read the problem to solve.
         */
        virtual void parse() = 0;

    protected:

        /**
         * Checks whether the given literal is correct w.r.t. the expected
         * number of variables.
         *
         * @param literal The literal to check.
         *
         * @return The given literal.
         */
        [[nodiscard]] int checkLiteral(int literal) const;

        /**
         * Gives the concrete solver to feed while parsing the input.
         *
         * @return The solver to feed.
         */
        virtual Universe::IUniverseSolver *getConcreteSolver();

    };

}

#endif
