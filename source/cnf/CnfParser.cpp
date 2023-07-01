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
 * @file CnfParser.cpp
 * @brief Defines the parser for parsing CNF problems (in the DIMACS format).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <crillab-except/except.hpp>

#include "crillab-autis/cnf/CnfParser.hpp"

using namespace Autis;
using namespace Except;
using namespace std;
using namespace Universe;

CnfParser::CnfParser(Scanner &scanner, IUniverseSatSolver *solver) :
        AbstractParser(scanner, solver) {
    // Nothing to do: everything already initialized.
}

void CnfParser::parse() {
    vector<int> clause;
    bool inClause = false;
    int nbClausesRead = 0;

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
        throw ParseException("Unexpected number of clauses");
    }
}

IUniverseSatSolver *CnfParser::getConcreteSolver() {
    return dynamic_cast<IUniverseSatSolver *>(AbstractParser::getConcreteSolver());
}
