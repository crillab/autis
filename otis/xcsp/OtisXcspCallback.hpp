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
    std::vector<Universe::BigInteger> toBigIntegerVector(std::vector<int>& vec) const;
    std::vector<string> toString(std::vector<XCSP3Core::XVariable *> &list) const;
    std::vector<std::vector<Universe::BigInteger>> toVectorOfVectorBigInteger(std::vector<std::vector<int>>& vec) const;
public:
    explicit OtisXcspCallback(Universe::IUniverseCspSolver* solver);

    void buildVariableInteger(string id, int minValue, int maxValue) override;

    void buildVariableInteger(string id, vector<int> &values) override;

    void beginVariableArray(string id) override;

    void endVariableArray() override;

    void
    buildObjectiveMaximize(XCSP3Core::ExpressionObjective type, vector<XCSP3Core::XVariable *> &list, vector<int> &coefs) override;

    void buildConstraintExtension(string id, vector<XCSP3Core::XVariable *> list, vector<vector<int>> &tuples, bool support,
                                  bool hasStar) override;

    void buildConstraintExtension(string id, XCSP3Core::XVariable *variable, vector<int> &tuples, bool support,
                                  bool hasStar) override;

    void buildConstraintExtensionAs(string id, vector<XCSP3Core::XVariable *> list, bool support, bool hasStar) override;

    void
    buildConstraintSum(string id, vector<XCSP3Core::XVariable *> &list, vector<int> &coeffs, XCSP3Core::XCondition &cond) override;

    void buildConstraintSum(string id, vector<XCSP3Core::XVariable *> &list, XCSP3Core::XCondition &cond) override;

    void buildConstraintSum(string id, vector<XCSP3Core::XVariable *> &list, vector<XCSP3Core::XVariable *> &coeffs,
                            XCSP3Core::XCondition &cond) override;

    void buildConstraintSum(string id, vector<XCSP3Core::Tree *> &trees, XCSP3Core::XCondition &cond) override;

    void buildConstraintSum(string id, vector<XCSP3Core::Tree *> &trees, vector<int> &coefs, XCSP3Core::XCondition &cond) override;

    void buildConstraintIntension(string id, string expr) override;

    void buildConstraintIntension(string id, XCSP3Core::Tree *tree) override;


};

} // Otis

#endif //OTIS_OTISXCSPCALLBACK_HPP
