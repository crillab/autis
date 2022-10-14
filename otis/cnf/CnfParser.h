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

#ifndef OTIS_CNFPARSER_H
#define OTIS_CNFPARSER_H

#include "../core/AbstractParser.h"
#include "../../libs/universe/universe/include/sat/IUniverseSatSolver.hpp"
namespace Otis {

    /**
     * The CnfParser specializes AbstractParser to read inputs written
     * using the CNF format.
     *
     * @version 0.1.0
     */
    class CnfParser : public Otis::AbstractParser {

    public:

        /**
         * Creates a new CnfParser which uses the given scanner and notifies
         * the given listener.
         *
         * @param scanner The scanner used to read the input stream.
         * @param listener The listener to notify.
         */
        explicit CnfParser(Otis::Scanner &scanner, Universe::IUniverseSatSolver *listener);

        /**
         * Parses the input to read the problem to solve.
         */
        void parse() override;


        virtual ~CnfParser()=default;

    protected:
        Universe::IUniverseSatSolver *getConcreteSolver() override;

    };

}

#endif
