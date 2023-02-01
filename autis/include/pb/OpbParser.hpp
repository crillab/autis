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
 * @file OpbParser.hpp
 * @brief Defines the parser for parsing pseudo-Boolean problems (in the OPB format).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef AUTIS_OPBPARSER_HPP
#define AUTIS_OPBPARSER_HPP

#include <fstream>
#include <string>
#include <vector>

#include "../../../libs/universe/universe/include/pb/IUniversePseudoBooleanSolver.hpp"

#include "../core/AbstractParser.hpp"

namespace Autis {

    /**
     * The OpbParser specializes AbstractParser to read inputs written
     * using the OPB format.
     */
    class OpbParser : public Autis::AbstractParser {
    private:
        bool optimization;
    public:

        /**
         * Creates a new OpbParser which uses the given scanner and notifies
         * the given listener.
         *
         * @param scanner The scanner used to read the input stream.
         * @param solver The solver to feed while parsing the instance.
         */
        explicit OpbParser(Autis::Scanner &scanner, Universe::IUniversePseudoBooleanSolver *solver);

        /**
         * Destroys this OpbParser.
         */
        ~OpbParser() override = default;

        /**
         * Parses the input to read the problem to solve.
         */
        void parse() override;

        bool isOptimization() override;

    private:

        /**
         * Reads the first comment line to get the number of variables and
         * the number of constraints in the input.
         */
        void readMetaData();

        /**
         * Skips comments from the input.
         */
        void skipComments();

        /**
         * Reads the objective line (if any).
         */
        void readObjective();

        /**
         * Reads a constraint.
         */
        void readConstraint();

        /**
         * Reads a term (either from the objective function or from a constraint)
         * and stores it into coefficient and literals.
         *
         * @param coefficient The coefficient of the term.
         * @param literals The literals of the term (if there is more than one,
         *        this is a product of literals).
         */
        void readTerm(Universe::BigInteger &coefficient, std::vector<int> &literals);

        /**
         * Reads an identifier from the stream and appends it to literals.
         *
         * @param literals The current list of read identifiers.
         *
         * @return Whether an identifier was read.
         */
        bool readIdentifier(std::vector<int> &literals);

        /**
         * Reads a relational operator from the input stream and stores it into
         * relationalOperator.
         *
         * @param relationalOperator The reference in which to hold the relational
         *        operator that has been read.
         */
        void readRelationalOperator(std::string &relationalOperator);

    protected:

        /**
         * Gives the pseudo-Boolean solver to feed while parsing the input.
         *
         * @return The solver to feed.
         */
        Universe::IUniversePseudoBooleanSolver *getConcreteSolver() override;

    };

}

#endif
