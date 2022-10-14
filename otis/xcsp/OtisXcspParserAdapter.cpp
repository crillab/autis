/**
* @file OtisXcspParserAdapter.cpp
* @brief
* @author Thibault Falque
* @version 0.1.0
* @date 19/09/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
*/


#include "OtisXcspParserAdapter.hpp"
#include "../../libs/xcsp3-cpp-parser/include/XCSP3CoreParser.h"
#include "OtisXcspCallback.hpp"

namespace Otis {
    OtisXCSPParserAdapter::OtisXCSPParserAdapter(Scanner &scanner, Universe::IUniverseCspSolver* solver) : AbstractParser(scanner,
                                                                                                             solver) {}
    void OtisXCSPParserAdapter::parse() {
        OtisXcspCallback cb(getConcreteSolver());
        XCSP3Core::XCSP3CoreParser parser(&cb);
        parser.parse(scanner.getInput());
    }

    Universe::IUniverseCspSolver* OtisXCSPParserAdapter::getConcreteSolver() {
        return (Universe::IUniverseCspSolver*)AbstractParser::getConcreteSolver();
    }


} // Otis