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
 * @file parser.cpp
 * @brief Provides a sober interface for parsing combinatorial problems.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <crillab-except/except.hpp>

#include "crillab-autis/cnf/CnfParser.hpp"
#include "crillab-autis/core/parser.hpp"
#include "crillab-autis/core/Scanner.hpp"
#include "crillab-autis/pb/OpbParser.hpp"
#include "crillab-autis/xcsp/AutisXcspParserAdapter.hpp"

using namespace Autis;
using namespace Except;
using namespace std;
using namespace Universe;

IUniverseSolver *Autis::parse(const string &path, IUniverseSolverFactory &listener) {
    ifstream input(path);
    return parse(input, listener);
}

Universe::IUniverseSolver *Autis::parse(istream &input, IUniverseSolverFactory &factory) {
    Scanner scanner(input);
    AbstractParser *parser;
    IUniverseSolver *solver;
    char c;

    if (!scanner.look(c)) {
        // The input stream is empty.
        throw ParseException("Input is empty");
    }

    if ((c == 'c') || (c == 'p')) {
        // The input uses the CNF format.
        solver = factory.createSatSolver();
        parser = new CnfParser(scanner, dynamic_cast<IUniverseSatSolver *>(solver));

    } else if (c == '*') {
        // The input uses the OPB format.
        solver = factory.createPseudoBooleanSolver();
        parser = new OpbParser(scanner, dynamic_cast<IUniversePseudoBooleanSolver *>(solver));

    } else if (c == '<') {
        // The input uses the XCSP3 format.
        solver = factory.createCspSolver();
        parser = new AutisXCSPParserAdapter(scanner, dynamic_cast<IUniverseCspSolver *>(solver));

    } else {
        // The format is not recognized.
        throw ParseException("Could not determine input type");
    }

    parser->parse();
    delete parser;
    return solver;
}
