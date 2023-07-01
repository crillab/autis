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
 * @file AutisXCSPParserAdapter.cpp
 * @brief Defines the parser for parsing XCSP3 problems (in the OPB format).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "crillab-autis/xcsp/AutisXcspParserAdapter.hpp"

#include <crillab-universe/csp/UniverseJavaCspSolver.hpp>
#include "crillab-autis/xcsp/AutisXcspCallback.hpp"
#include "XCSP3CoreParser.h"

using namespace Autis;
using namespace Universe;
using namespace XCSP3Core;

AutisXCSPParserAdapter::AutisXCSPParserAdapter(
    Scanner &scanner, IUniverseCspSolver *solver, XCSP3CoreCallbacks *callback) : AbstractParser(scanner, solver),
                                                                                  callback(callback) {
    // Nothing to do: everything is already initialized.
}

void AutisXCSPParserAdapter::parse() {
    if (callback == nullptr) {
        // Inferring the most appropriate callback to use.
        AutisXcspCallback *cb = getCallback();
        XCSP3CoreParser parser(cb);
        parser.parse(scanner.getInput());
        optimization = parser.isOptimization();
        delete cb;

    } else {
        // Using the specified callback to parse the input.
        XCSP3CoreParser parser(callback);
        parser.parse(scanner.getInput());
        optimization = parser.isOptimization();
    }
}

Autis::AutisXcspCallback *AutisXCSPParserAdapter::getCallback() {
    auto concreteSolver = getConcreteSolver();
    auto javaSolver = dynamic_cast<UniverseJavaCspSolver *>(concreteSolver);

    if (javaSolver == nullptr) {
        // The solver is not a Java solver: using a native callback.
        return AutisXcspCallback::newNativeInstance(concreteSolver);
    }

    // The solver is a Java solver: using a java callback.
    return AutisXcspCallback::newJavaInstance(javaSolver);
}

IUniverseCspSolver *AutisXCSPParserAdapter::getConcreteSolver() {
    return dynamic_cast<IUniverseCspSolver *>(AbstractParser::getConcreteSolver());
}

bool AutisXCSPParserAdapter::isOptimization() {
    return optimization;
}
