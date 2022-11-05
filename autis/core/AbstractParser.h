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
* @file AbstractParser.h
* @brief This file represents the header of the abstract class AbstractParser.
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
* @license GNU LGPL 3
*/

#ifndef AUTIS_ABSTRACTPARSER_H
#define AUTIS_ABSTRACTPARSER_H

#include <istream>
#include <memory>

#include "Scanner.h"
#include "../../libs/universe/universe/include/core/IUniverseSolver.hpp"

namespace Autis {

    /**
     * @class AbstractParser
     * @brief The AbstractParser is the parent class of classes used to parse
     * input streams so as to read a problem to solve.
     *
     * @version 0.1.0
     */
    class AbstractParser {

    protected:

        /**
         * The scanner used to read the input stream.
         */
        Autis::Scanner &scanner;

        /**
         * The listener to notify while parsing.
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

        /**
         * @fn AbstractParser(Autis::Scanner &scanner, Universe::IUniverseSolver* solver)
         * @brief Creates a new parser which uses the given scanner and notifies
         * the given listener.
         *
         * @param scanner The scanner used to read the input stream.
         * @param solver The solver to notify.
         */
        explicit AbstractParser(Autis::Scanner &scanner,
                                Universe::IUniverseSolver* solver);

        /**
         * @fn checkLiteral(int literal)
         * @brief Checks whether the given literal is correct w.r.t. the expected
         * number of variables.
         *
         * @param literal The literal to check.
         *
         * @return The given literal.
         */
        [[nodiscard]] int checkLiteral(int literal) const;


        virtual Universe::IUniverseSolver* getConcreteSolver();


    public:

        /**
         * @fn parse()
         * @brief Parses the input to read the problem to solve.
         */
        virtual void parse() = 0;

        virtual ~AbstractParser()=default;

    };

}

#endif
