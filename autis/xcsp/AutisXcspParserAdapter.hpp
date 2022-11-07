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
* @file AutisXcspParserAdapter.hpp
* @brief
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 19/09/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
* @license GNU LGPL 3
*/


#ifndef AUTIS_AUTISXCSPPARSERADAPTER_HPP
#define AUTIS_AUTISXCSPPARSERADAPTER_HPP

#include "../core/AbstractParser.hpp"
#include "../../libs/universe/universe/include/csp/IUniverseCspSolver.hpp"

namespace Autis {

/**
* @class AutisXCSPParserAdapter
* @brief 
*/
    class AutisXCSPParserAdapter: public AbstractParser {
    public:
        AutisXCSPParserAdapter(Scanner &scanner, Universe::IUniverseCspSolver* listener);

        void parse() override;

    protected:
        Universe::IUniverseCspSolver*getConcreteSolver() override;
    };

} // Autis

#endif //AUTIS_AUTISXCSPPARSERADAPTER_HPP
