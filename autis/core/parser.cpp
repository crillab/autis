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

void Autis::parse(const string &path, Universe::ISolverFactory &listener) {
    ifstream input(path);
    parse(input, listener);
}

void Autis::parse(istream &input, Universe::ISolverFactory &factory) {
    char c;
    Scanner scanner(input);
    unique_ptr<AbstractParser> parser;

    if (!scanner.look(c)) {
        // The input stream is empty.
        throw Except::ParseException("Input is empty");
    }
    if ((c == 'c') || (c == 'p')) {
        // The input uses the CNF format.
        parser = make_unique<CnfParser>(scanner, factory.createSatSolver());

    } else if (c == '*') {
        // The input uses the OPB format.
        parser = make_unique<OpbParser>(scanner, factory.createPseudoBooleanSolver());
    }else if(c=='<'){
            parser = make_unique<AutisXCSPParserAdapter>(scanner, factory.createCspSolver());
    } else {
        // The format is not recognized.
        throw Except::ParseException("Could not determine input type");
    }
    parser->parse();
}
