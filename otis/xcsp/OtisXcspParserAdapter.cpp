/**
* @file OtisXcspParserAdapter.cpp
* @brief
* @author Thibault Falque
* @version 0.1.0
* @date 19/09/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
*/


#include "OtisXcspParserAdapter.hpp"

namespace Otis {
    OtisXCSPParserAdapter::OtisXCSPParserAdapter(Scanner &scanner, ParseListener &listener) : AbstractParser(scanner,
                                                                                                             listener) {}
    void OtisXCSPParserAdapter::parse() {

    }


} // Otis