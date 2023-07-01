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
 * @file parser.hpp
 * @brief Provides a sober interface for parsing combinatorial problems.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef AUTIS_PARSER_HPP
#define AUTIS_PARSER_HPP

#include <string>

#include <crillab-universe/utils/IUniverseSolverFactory.hpp>

namespace Autis {

    /**
     * Parses the file at the given path to read the formula to solve.
     * The format of the input file may be CNF, OPB or XCSP3.
     *
     * @param path The path of the file to parse.
     * @param listener The listener to notify while parsing.
     */
    Universe::IUniverseSolver *parse(
            const std::string &path, Universe::IUniverseSolverFactory &listener);

    /**
     * Parses the given stream to read the formula to solve.
     * The format of the input file may be CNF, OPB or XCSP3.
     *
     * @param input The input stream to parse.
     * @param factory The listener to notify while parsing.
     */
    Universe::IUniverseSolver *parse(
            std::istream &input, Universe::IUniverseSolverFactory &factory);

}

#endif
