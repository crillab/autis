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
* @file OtisXcspCallback.hpp
* @brief 
* @license This project is released under the GNU LGPL3 License.
*/

#ifndef OTIS_OTISXCSPCALLBACK_HPP
#define OTIS_OTISXCSPCALLBACK_HPP

#include "../../libs/xcsp3-cpp-parser/include/XCSP3CoreCallbacks.h"
#include "../../libs/universe/universe/include/csp/IUniverseCspSolver.hpp"

namespace Otis {
/**
@class OtisXcspCallback
@brief Header for the class OtisXcspCallback. 
@file OtisXcspCallback.hpp
*/
class OtisXcspCallback: public XCSP3Core::XCSP3CoreCallbacks {
private:
    Universe::IUniverseCspSolver* solver;
public:
    explicit OtisXcspCallback(Universe::IUniverseCspSolver* solver);

    void buildVariableInteger(string id, int minValue, int maxValue) override;

    void buildVariableInteger(string id, vector<int> &values) override;
};

} // Otis

#endif //OTIS_OTISXCSPCALLBACK_HPP
