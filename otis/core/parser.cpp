/******************************************************************************
 * OTIS - Opening wriTing and readIng instanceS                               *
 * Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.                   *
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
 * If not, see {@link http:www.gnu.orglicenses}.                              *
 ******************************************************************************/

#include <memory>

#include "../cnf/CnfParser.h"
#include "../pb/OpbParser.h"
#include "Scanner.h"
#include "parser.h"
#include "../xcsp/OtisXcspParserAdapter.hpp"
#include "../../libs/exception/except/except.hpp"

using namespace std;
using namespace Otis;

void Otis::parse(const string &path, ParseListener &listener) {
    ifstream input(path);
    parse(input, listener);
}

void Otis::parse(istream &input, ParseListener &listener) {
    char c;
    Scanner scanner(input);
    unique_ptr<AbstractParser> parser;

    if (!scanner.look(c)) {
        // The input stream is empty.
        throw Except::ParseException("Input is empty");
    }
    if ((c == 'c') || (c == 'p')) {
        // The input uses the CNF format.
        parser = make_unique<CnfParser>(scanner, listener);

    } else if (c == '*') {
        // The input uses the OPB format.
        parser = make_unique<OpbParser>(scanner, listener);
    }else if(c=='<'){
            parser = make_unique<OtisXCSPParserAdapter>(scanner, listener);
    } else {
        // The format is not recognized.
        throw Except::ParseException("Could not determine input type");
    }
    parser->parse();
}
