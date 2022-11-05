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

#ifndef AUTIS_PARSER_H
#define AUTIS_PARSER_H

#include <string>

#include "../../libs/universe/universe/include/utils/ISolverFactory.hpp"
namespace Autis {

    /**
     * Parses the file at the given path to read the formula to solve.
     * The format of the input file may be CNF or OPB.
     *
     * @param path The path of the file to parse.
     * @param listener The listener to notify while parsing.
     */
    void parse(const std::string &path, Universe::ISolverFactory &listener);

    /**
     * Parses the given input stream to read the formula to solve.
     * The format of the input may be CNF or OPB.
     *
     * @param input The input stream to parse.
     * @param factory The listener to notify while parsing.
     */
    void parse(std::istream &input, Universe::ISolverFactory &factory);

}

#endif
