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
* @file AbstractParser.cpp
* @brief This file represents the definition of the abstract class AbstractParser.
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
* @license GNU LGPL 3
*/

#include "AbstractParser.h"
#include "../../libs/exception/except/except.hpp"


using namespace std;
using namespace Autis;

AbstractParser::AbstractParser(Scanner &scanner, Universe::IUniverseSolver* solver) :
        scanner(scanner),
        solver(solver),
        numberOfVariables(0),
        numberOfConstraints(0) {
    // Nothing to do: all fields are already initialized.
}

int AbstractParser::checkLiteral(int literal) const {
    int variable = abs(literal);
    if ((variable == 0) || (variable > numberOfVariables)) {
        throw Except::ParseException("An invalid literal has been read");
    }
    return literal;
}

Universe::IUniverseSolver *AbstractParser::getConcreteSolver() {
    return solver;
}
