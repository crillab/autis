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
 * @file AutisXCSPParserAdapter.hpp
 * @brief Defines a parser adapting the callback defined in XCSP3-CPP-Parser.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/09/2022
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef AUTIS_AUTISXCSPPARSERADAPTER_HPP
#define AUTIS_AUTISXCSPPARSERADAPTER_HPP

#include "../../libs/universe/universe/include/csp/IUniverseCspSolver.hpp"

#include "../core/AbstractParser.hpp"

namespace Autis {

    /**
     * The AutisXCSPParserAdapter class defines an adapter for the callback interface
     * defined in XCSP3-CPP-Parser, to use it as an AbstractParser.
     */
    class AutisXCSPParserAdapter : public AbstractParser {

    private:

        /**
         * The callback to use when parsing the input instance.
         */
        XCSP3Core::XCSP3CoreCallbacks *callback;

    public:

        /**
         * Creates a new AutisXCSPParserAdapter.
         *
         * @param scanner The scanner to use to read the input instance.
         * @param solver The solver to feed while parsing the instance.
         * @param callback The callback to use when parsing the input instance.
         */
        AutisXCSPParserAdapter(Autis::Scanner &scanner, Universe::IUniverseCspSolver *solver,
                               XCSP3Core::XCSP3CoreCallbacks *callback = nullptr);

        /**
         * Parses the input instance, and feeds the associated solver with the read constraints.
         */
        void parse() override;

    protected:

        /**
         * Gives the callback implementation that matches the actual type of the
         * solver to feed.
         *
         * @return The callback to use when parsing the input instance.
         */
        virtual Autis::AutisXcspCallback *getCallback();

        /**
         * Gives the CSP solver to feed while parsing.
         *
         * @return The CSP solver to feed.
         */
        Universe::IUniverseCspSolver *getConcreteSolver() override;

    };

}

#endif
