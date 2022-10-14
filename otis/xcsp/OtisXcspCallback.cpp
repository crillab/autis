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

/**
* @author Thibault Falque
* @author Romain Wallon 
* @date  18/09/2022
* @file OtisXcspCallback.cpp
* @brief 
* @license This project is released under the GNU LGPL3 License.
*/

#include "OtisXcspCallback.hpp"

namespace Otis {
    OtisXcspCallback::OtisXcspCallback(Universe::IUniverseCspSolver* solver) : solver(solver) {}

    void OtisXcspCallback::buildVariableInteger(string id, int minValue, int maxValue) {

    }

    void OtisXcspCallback::buildVariableInteger(string id, vector<int> &values) {

    }

} // Otis