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
 * @file CnfParser.hpp
 * @brief Defines the parser for parsing CNF problems (in the DIMACS format).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef AUTIS_CNFPARSER_HPP
#define AUTIS_CNFPARSER_HPP

#include "../../../libs/universe/universe/include/sat/IUniverseSatSolver.hpp"

#include "../core/AbstractParser.hpp"

namespace Autis {

    /**
     * The CnfParser specializes AbstractParser to read inputs written
     * using the CNF format.
     */
    class CnfParser : public Autis::AbstractParser {

    public:

        /**
         * Creates a new CnfParser.
         *
         * @param scanner The scanner used to read the input stream.
         * @param solver The solver to feed while parsing the instance.
         */
        explicit CnfParser(Autis::Scanner &scanner, Universe::IUniverseSatSolver *solver);

        /**
         * Destroys this CnfParser.
         */
        ~CnfParser() override = default;

        /**
         * Parses the input to read the problem to solve.
         */
        void parse() override;

    protected:

        /**
         * Gives the SAT solver to feed while parsing the input.
         *
         * @return The solver to feed.
         */
        Universe::IUniverseSatSolver *getConcreteSolver() override;

    };

}

#endif
