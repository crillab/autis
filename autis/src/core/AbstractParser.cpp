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
 * @file AbstractParser.cpp
 * @brief Defines the base class for all parsers implemented in Autis.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../libs/exception/except/except.hpp"

#include "../../include/core/AbstractParser.hpp"

using namespace Autis;
using namespace Except;
using namespace std;
using namespace Universe;

AbstractParser::AbstractParser(Scanner &scanner, IUniverseSolver *solver) :
        scanner(scanner),
        solver(solver),
        numberOfVariables(0),
        numberOfConstraints(0) {
    // Nothing to do: everything is already initialized.
}

int AbstractParser::checkLiteral(int literal) const {
    int variable = abs(literal);
    if ((variable == 0) || (variable > numberOfVariables)) {
        throw ParseException("An invalid literal has been read");
    }
    return literal;
}

IUniverseSolver *AbstractParser::getConcreteSolver() {
    return solver;
}
