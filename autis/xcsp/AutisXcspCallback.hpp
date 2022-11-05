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
* @file AutisXcspCallback.hpp
* @brief
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 19/09/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
* @license GNU LGPL 3
*/

#ifndef AUTIS_AUTISXCSPCALLBACK_HPP
#define AUTIS_AUTISXCSPCALLBACK_HPP

#include "../../libs/xcsp3-cpp-parser/include/XCSP3CoreCallbacks.h"
#include "../../libs/universe/universe/include/csp/IUniverseCspSolver.hpp"

namespace Autis {
/**
@class AutisXcspCallback
@brief Header for the class AutisXcspCallback.
@file AutisXcspCallback.hpp
*/
class AutisXcspCallback: public XCSP3Core::XCSP3CoreCallbacks {
private:
    Universe::IUniverseCspSolver* solver;
    std::vector<Universe::BigInteger> toBigIntegerVector(std::vector<int>& vec) const;
    std::vector<string> toString(std::vector<XCSP3Core::XVariable *> &list) const;
    std::vector<std::vector<Universe::BigInteger>> toVectorOfVectorBigInteger(std::vector<std::vector<int>>& vec) const;
public:
    explicit AutisXcspCallback(Universe::IUniverseCspSolver* solver);

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

    void buildConstraintAlldifferent(string id, vector<XCSP3Core::XVariable *> &list) override;

private:

    Universe::IUniverseIntensionConstraint *createIntension(XCSP3Core::Node *node);

};

} // Autis

#endif //AUTIS_AUTISXCSPCALLBACK_HPP
