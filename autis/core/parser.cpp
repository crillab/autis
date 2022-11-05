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


#include <memory>

#include "../cnf/CnfParser.h"
#include "../pb/OpbParser.h"
#include "Scanner.h"
#include "parser.h"
#include "../xcsp/AutisXcspParserAdapter.hpp"
#include "../../libs/exception/except/except.hpp"


using namespace std;
using namespace Autis;

Universe::IUniverseSolver * Autis::parse(const string &path, Universe::ISolverFactory &listener) {
    ifstream input(path);
    return parse(input, listener);
}

Universe::IUniverseSolver *Autis::parse(istream &input, Universe::ISolverFactory &factory) {
    char c;
    Scanner scanner(input);
    unique_ptr<AbstractParser> parser;
    Universe::IUniverseSolver *solver;
    if (!scanner.look(c)) {
        // The input stream is empty.
        throw Except::ParseException("Input is empty");
    }
    if ((c == 'c') || (c == 'p')) {
        solver = factory.createSatSolver();
        // The input uses the CNF format.
        parser = make_unique<CnfParser>(scanner, dynamic_cast<Universe::IUniverseSatSolver *>(solver));

    } else if (c == '*') {
        solver = factory.createPseudoBooleanSolver();
        // The input uses the OPB format.
        parser = make_unique<OpbParser>(scanner, dynamic_cast<Universe::IUniversePseudoBooleanSolver *>(solver));
    } else if (c == '<') {
        solver = factory.createCspSolver();
        parser = make_unique<AutisXCSPParserAdapter>(scanner, dynamic_cast<Universe::IUniverseCspSolver *>(solver));
    } else {
        // The format is not recognized.
        throw Except::ParseException("Could not determine input type");
    }
    parser->parse();
    return solver;
}
