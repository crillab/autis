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
 * @file IUniverseSolver.hpp
 * @brief Defines an interface for any kind of solvers.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "AutisXcspCallback.hpp"
#include "../../../libs/universe/universe/include/csp/intension/UniverseJavaIntensionConstraintFactory.hpp"

using namespace XCSP3Core;

namespace Autis {
    AutisXcspCallback::AutisXcspCallback(Universe::IUniverseCspSolver* solver) : solver(solver) {}

    void AutisXcspCallback::buildVariableInteger(string id, int minValue, int maxValue) {
        solver->newVariable(id,minValue,maxValue);
    }

    void AutisXcspCallback::buildVariableInteger(string id, vector<int> &values) {
        solver->newVariable(id,values);
    }

    void AutisXcspCallback::buildConstraintIntension(string id, string expr) {
        XCSP3CoreCallbacks::buildConstraintIntension(id, expr);
    }

    void AutisXcspCallback::buildConstraintIntension(string id, XCSP3Core::Tree *tree) {
        solver->addIntension(createIntension(tree->root));
    }

    void AutisXcspCallback::buildObjectiveMaximize(XCSP3Core::ExpressionObjective type, vector<XVariable *> &list,
                                                   vector<int> &coefs) {
        vector<string> vars = toString(list);

        solver->maximizeSum(vars,this->toBigIntegerVector(coefs));
    }


    void AutisXcspCallback::buildConstraintExtension(string id, vector<XVariable *> list, vector<vector<int>> &tuples,
                                                     bool support, bool hasStar) {
        if(hasStar){
            throw runtime_error("Unsupported exception: hasStar");
        }
        if(support) {
            solver->addSupport(toString(list), toVectorOfVectorBigInteger(tuples));
        }else{
            solver->addConflicts(toString(list), toVectorOfVectorBigInteger(tuples));
        }
    }

    void AutisXcspCallback::buildConstraintExtension(string id, XCSP3Core::XVariable *variable, vector<int> &tuples,
                                                     bool support, bool hasStar) {
        if(hasStar){
            throw runtime_error("Unsupported exception: hasStar");
        }
        if(support) {
            solver->addSupport(variable->id, toBigIntegerVector(tuples));
        }else{
            solver->addConflicts(variable->id, toBigIntegerVector(tuples));
        }
    }

    void AutisXcspCallback::buildConstraintExtensionAs(string id, vector<XVariable *> list, bool support, bool hasStar) {
        XCSP3CoreCallbacks::buildConstraintExtensionAs(id, list, support, hasStar);
    }

    void AutisXcspCallback::buildConstraintSum(string id, vector<XVariable *> &list, vector<int> &coeffs,
                                               XCSP3Core::XCondition &cond) {
        XCSP3CoreCallbacks::buildConstraintSum(id, list, coeffs, cond);
    }

    void AutisXcspCallback::buildConstraintSum(string id, vector<XVariable *> &list, XCSP3Core::XCondition &cond) {
        XCSP3CoreCallbacks::buildConstraintSum(id, list, cond);
    }

    void AutisXcspCallback::buildConstraintSum(string id, vector<XVariable *> &list, vector<XVariable *> &coeffs,
                                               XCSP3Core::XCondition &cond) {
        XCSP3CoreCallbacks::buildConstraintSum(id, list, coeffs, cond);
    }

    void AutisXcspCallback::buildConstraintSum(string id, vector<Tree *> &trees, XCSP3Core::XCondition &cond) {
        XCSP3CoreCallbacks::buildConstraintSum(id, trees, cond);
    }

    void AutisXcspCallback::buildConstraintSum(string id, vector<Tree *> &trees, vector<int> &coefs,
                                               XCSP3Core::XCondition &cond) {
        XCSP3CoreCallbacks::buildConstraintSum(id, trees, coefs, cond);
    }

    void AutisXcspCallback::buildConstraintAlldifferent(string id, vector<XVariable *> &list) {
        solver->addAllDifferent(toString(list));
    }

    std::vector<Universe::BigInteger> AutisXcspCallback::toBigIntegerVector(std::vector<int>& vec) const{
        std::vector<Universe::BigInteger> lists;
        for(auto i:vec){
            lists.push_back(i);
        }
        return lists;
    }

    std::vector<std::vector<Universe::BigInteger>> AutisXcspCallback::toVectorOfVectorBigInteger(std::vector<std::vector<int>>& vec) const{
        std::vector<std::vector<Universe::BigInteger>> lists;
        for(auto i:vec){
            lists.push_back(toBigIntegerVector(i));
        }
        return lists;
    }

    std::vector<string> AutisXcspCallback::toString(std::vector<XVariable *> &list) const {
        vector<string> vars;
        for(auto xv:list){
            vars.push_back(xv->id);
        }
        return vars;
    }

    void AutisXcspCallback::beginVariableArray(string id) {
        //XCSP3CoreCallbacks::beginVariableArray(id);
    }

    void AutisXcspCallback::endVariableArray() {
        //XCSP3CoreCallbacks::endVariableArray();
    }

} // Autis