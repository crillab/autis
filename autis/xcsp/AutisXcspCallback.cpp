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
* @file AutisXcspCallback.cpp
* @brief
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 19/09/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
* @license GNU LGPL 3
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

    Universe::IUniverseIntensionConstraint *AutisXcspCallback::createIntension(Node *node) {
        if (node->type == ExpressionType::ODECIMAL) {
            return Universe::UniverseJavaIntensionConstraintFactory::constant((long) ((NodeConstant *) node)->val);
        }

        if (node->type == ExpressionType::OVAR) {
            return Universe::UniverseJavaIntensionConstraintFactory::variable(((NodeVariable *) node)->var);
        }

        switch (node->type) {
            case ExpressionType::OABS: {
                auto child = createIntension(node->parameters[0]);
                return Universe::UniverseJavaIntensionConstraintFactory::abs(child);
            }
            case ExpressionType::OADD: {
                std::vector<Universe::IUniverseIntensionConstraint*> constrs;
                for (auto child : node->parameters) {
                    constrs.push_back(createIntension(child));
                }
                return Universe::UniverseJavaIntensionConstraintFactory::add(constrs);
            }
            case ExpressionType::ODIST: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::dist(child1, child2);
            }
            case ExpressionType::ODIV: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::div(child1, child2);
            }
            case ExpressionType::OMAX: {
                std::vector<Universe::IUniverseIntensionConstraint*> constrs;
                for (auto child : node->parameters) {
                    constrs.push_back(createIntension(child));
                }
                return Universe::UniverseJavaIntensionConstraintFactory::max(constrs);
            }
            case ExpressionType::OMIN: {
                std::vector<Universe::IUniverseIntensionConstraint*> constrs;
                for (auto child : node->parameters) {
                    constrs.push_back(createIntension(child));
                }
                return Universe::UniverseJavaIntensionConstraintFactory::min(constrs);
            }
            case ExpressionType::OMOD: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::mod(child1, child2);
            }
            case ExpressionType::OMUL: {
                std::vector<Universe::IUniverseIntensionConstraint*> constrs;
                for (auto child : node->parameters) {
                    constrs.push_back(createIntension(child));
                }
                return Universe::UniverseJavaIntensionConstraintFactory::mult(constrs);
            }
            case ExpressionType::ONEG: {
                auto child = createIntension(node->parameters[0]);
                return Universe::UniverseJavaIntensionConstraintFactory::neg(child);
            }
            case ExpressionType::OPOW: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::pow(child1, child2);
            }
            case ExpressionType::OSQR: {
                auto child = createIntension(node->parameters[0]);
                return Universe::UniverseJavaIntensionConstraintFactory::sqr(child);
            }
            case ExpressionType::OSUB: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::sub(child1, child2);
            }
            case ExpressionType::OIFF: {
                std::vector<Universe::IUniverseIntensionConstraint*> constrs;
                for (auto child : node->parameters) {
                    constrs.push_back(createIntension(child));
                }
                return Universe::UniverseJavaIntensionConstraintFactory::equiv(constrs);
            }
            case ExpressionType::OAND: {
                std::vector<Universe::IUniverseIntensionConstraint*> constrs;
                for (auto child : node->parameters) {
                    constrs.push_back(createIntension(child));
                }
                return Universe::UniverseJavaIntensionConstraintFactory::conjunction(constrs);
            }
            case ExpressionType::OIMP: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::impl(child1, child2);
            }
            case ExpressionType::ONOT: {
                auto child = createIntension(node->parameters[0]);
                return Universe::UniverseJavaIntensionConstraintFactory::negation(child);
            }
            case ExpressionType::OOR: {
                std::vector<Universe::IUniverseIntensionConstraint*> constrs;
                for (auto child : node->parameters) {
                    constrs.push_back(createIntension(child));
                }
                return Universe::UniverseJavaIntensionConstraintFactory::disjunction(constrs);
            }
            case ExpressionType::OXOR: {
                std::vector<Universe::IUniverseIntensionConstraint*> constrs;
                for (auto child : node->parameters) {
                    constrs.push_back(createIntension(child));
                }
                return Universe::UniverseJavaIntensionConstraintFactory::parity(constrs);
            }
            case ExpressionType::OEQ: {
                std::vector<Universe::IUniverseIntensionConstraint*> constrs;
                for (auto child : node->parameters) {
                    constrs.push_back(createIntension(child));
                }
                return Universe::UniverseJavaIntensionConstraintFactory::eq(constrs);
            }
            case ExpressionType::OGE: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::ge(child1, child2);
            }
            case ExpressionType::OGT: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::gt(child1, child2);
            }
            case ExpressionType::OLE: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::le(child1, child2);
            }
            case ExpressionType::OLT: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::lt(child1, child2);
            }
            case ExpressionType::ONE: {
                auto child1 = createIntension(node->parameters[0]);
                auto child2 = createIntension(node->parameters[1]);
                return Universe::UniverseJavaIntensionConstraintFactory::neq(child1, child2);
            }
            default:
                throw std::runtime_error("No operator");
        }
    }

} // Autis