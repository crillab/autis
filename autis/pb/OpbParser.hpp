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
* @file OpbParser.h
* @brief This file represents the header of the OpbParser class.
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
* @license GNU LGPL 3
*/

#ifndef AUTIS_OPBPARSER_HPP
#define AUTIS_OPBPARSER_HPP

#include <fstream>
#include <string>
#include <vector>

#include "../core/AbstractParser.hpp"
#include "../../libs/universe/universe/include/pb/IUniversePseudoBooleanSolver.hpp"

namespace Autis {

    /**
     * @class OpbParser
     * @brief The OpbParser specializes AbstractParser to read inputs written
     * using the OPB format.
     *
     * @version 0.1.0
     */
    class OpbParser : public Autis::AbstractParser {

    public:

        /**
         * @fn OpbParser(Autis::Scanner &scanner, Universe::IUniversePseudoBooleanSolver *solver)
         * @brief Creates a new OpbParser which uses the given scanner and notifies
         * the given listener.
         *
         * @param scanner The scanner used to read the input stream.
         * @param listener The listener to notify.
         */
        OpbParser(Autis::Scanner &scanner, Universe::IUniversePseudoBooleanSolver *solver);

        /**
         * @fn parse()
         * @brief Parses the input to read the problem to solve.
         */
        void parse() override;

        virtual ~OpbParser()=default;
    protected:
        Universe::IUniversePseudoBooleanSolver *getConcreteSolver() override;

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

    };

}

#endif