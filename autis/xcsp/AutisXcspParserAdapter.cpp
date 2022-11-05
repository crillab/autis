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
* @file AutisXcspParserAdapter.cpp
* @brief
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 19/09/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
*/


#include "AutisXcspParserAdapter.hpp"
#include "../../libs/xcsp3-cpp-parser/include/XCSP3CoreParser.h"
#include "AutisXcspCallback.hpp"

namespace Autis {
    AutisXCSPParserAdapter::AutisXCSPParserAdapter(Scanner &scanner, Universe::IUniverseCspSolver* solver) : AbstractParser(scanner,
                                                                                                                            solver) {}
    void AutisXCSPParserAdapter::parse() {
        AutisXcspCallback cb(getConcreteSolver());
        XCSP3Core::XCSP3CoreParser parser(&cb);
        parser.parse(scanner.getInput());
    }

    Universe::IUniverseCspSolver* AutisXCSPParserAdapter::getConcreteSolver() {
        return dynamic_cast<Universe::IUniverseCspSolver*>(AbstractParser::getConcreteSolver());
    }


} // Autis