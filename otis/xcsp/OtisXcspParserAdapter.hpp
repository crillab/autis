/**
* @file OtisXcspParserAdapter.hpp
* @brief
* @author Thibault Falque
* @version 0.1.0
* @date 19/09/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
*/


#ifndef OTIS_OTISXCSPPARSERADAPTER_HPP
#define OTIS_OTISXCSPPARSERADAPTER_HPP

#include "../core/AbstractParser.h"

namespace Otis {

/**
* @class OtisXCSPParserAdapter
* @brief 
*/
    class OtisXCSPParserAdapter: public AbstractParser {
    public:
        OtisXCSPParserAdapter(Scanner &scanner, ParseListener &listener);

        void parse() override;
    };

} // Otis

#endif //OTIS_OTISXCSPPARSERADAPTER_HPP
