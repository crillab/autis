/******************************************************************************
 * AUTIS, a library for parsing combinatorial problems.                       *
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
 * @file AutisXCSPParserAdapter.cpp
 * @brief Defines a parser adapting the callback defined in XCSP3-CPP-Parser.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/09/2022
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../libs/xcsp3-cpp-parser/include/XCSP3CoreParser.h"
#include "../../libs/universe/universe/include/csp/UniverseJavaCspSolver.hpp"


#include "AutisXcspCallback.hpp"
#include "AutisJavaXcspCallback.hpp"
#include "AutisNativeXcspCallback.hpp"
#include "AutisXcspParserAdapter.hpp"

using namespace Autis;
using namespace Universe;
using namespace XCSP3Core;

AutisXCSPParserAdapter::AutisXCSPParserAdapter(Scanner &scanner,
                                               IUniverseCspSolver *solver, XCSP3CoreCallbacks *callback) :
        AbstractParser(scanner, solver),
        callback(callback) {
    // Nothing to do: everything is already initialized.
}

void AutisXCSPParserAdapter::parse() {
    if (callback == nullptr) {
        // Inferring the most appropriate callback to use.
        AutisXcspCallback *cb = getCallback();
        XCSP3CoreParser parser(cb);
        parser.parse(scanner.getInput());
        delete cb;

    } else {
        // Using the specified callback to parse the input.
        XCSP3CoreParser parser(callback);
        parser.parse(scanner.getInput());
    }
}

Autis::AutisXcspCallback *AutisXCSPParserAdapter::getCallback() {
    auto concreteSolver = getConcreteSolver();
    auto javaSolver = dynamic_cast<UniverseJavaCspSolver *>(concreteSolver);

    if (javaSolver == nullptr) {
        // The solver is not a Java solver: using a native callback.
        return new AutisNativeXcspCallback(concreteSolver);
    }

    // The solver is a Java solver: using a dedicated callback.
    return new AutisJavaXcspCallback(javaSolver);
}

IUniverseCspSolver *AutisXCSPParserAdapter::getConcreteSolver() {
    return dynamic_cast<IUniverseCspSolver *>(AbstractParser::getConcreteSolver());
}
