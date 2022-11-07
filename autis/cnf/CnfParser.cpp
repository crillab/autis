/******************************************************************************
 * AUTIS, a library for parsing combinatorial problems.                       *
 * Copyright (c) 2022 - Exakis Nelite, Univ Artois & CNRS.                    *
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
 * If not, see http//:www.gnu.org/licenses.                                   *
 ******************************************************************************/

/**
* @file CnfParser.cpp
* @brief This file represents the definition of the methods of the class CNFParser for parsing Dimacs CNF File.
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
* @license GNU LGPL 3
*/


#include "CnfParser.hpp"
#include "../../libs/exception/except/except.hpp"

using namespace std;
using namespace Autis;

CnfParser::CnfParser(Scanner &scanner, Universe::IUniverseSatSolver *solver) :
        AbstractParser(scanner, solver) {
    // Nothing to do: all fields are already initialized.
}

void CnfParser::parse() {
    bool inClause = false;
    int nbClausesRead = 0;

    std::vector<int> clause;

    for (char next; scanner.look(next);) {
        if (next == 'c') {
            // This is a comment to skip.
            scanner.skipLine();

        } else if (next == 'p') {
            // This is the problem description line.
            scanner.read(numberOfVariables);
            scanner.read(numberOfConstraints);
            scanner.skipLine();

        } else {
            // There is a literal to read.
            int literal = 0;
            scanner.read(literal);

            if (!inClause) {
                // This is a new clause to read.
                clause.clear();
                inClause = true;
                nbClausesRead++;
            }

            if (literal == 0) {
                // This is the end of a clause.
                getConcreteSolver()->addClause(clause);
                inClause = false;

            } else {
                // The literal is added if and only if it is correct.
                clause.push_back(checkLiteral(literal));
            }
        }
    }

    if (inClause) {
        // The last clause has not been added.
        getConcreteSolver()->addClause(clause);
    }

    if (nbClausesRead != numberOfConstraints) {
        // The number of read clauses is not the expected one.
        throw Except::ParseException("Unexpected number of clauses");
    }
}

Universe::IUniverseSatSolver *CnfParser::getConcreteSolver() {
    return dynamic_cast<Universe::IUniverseSatSolver *>(AbstractParser::getConcreteSolver());
}


