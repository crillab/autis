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
 * @file AutisJavaXcspCallback.cpp
 * @brief
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 09/11/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../libs/universe/universe/include/csp/intension/UniverseJavaIntensionConstraintFactory.hpp"

#include "AutisJavaXcspCallback.hpp"

using namespace Autis;
using namespace Universe;
using namespace XCSP3Core;

IUniverseIntensionConstraint *AutisJavaXcspCallback::createIntension(Node *node) {
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
            std::vector < Universe::IUniverseIntensionConstraint * > constrs;
            for (auto child: node->parameters) {
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
            std::vector < Universe::IUniverseIntensionConstraint * > constrs;
            for (auto child: node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return Universe::UniverseJavaIntensionConstraintFactory::max(constrs);
        }
        case ExpressionType::OMIN: {
            std::vector < Universe::IUniverseIntensionConstraint * > constrs;
            for (auto child: node->parameters) {
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
            std::vector < Universe::IUniverseIntensionConstraint * > constrs;
            for (auto child: node->parameters) {
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
            std::vector < Universe::IUniverseIntensionConstraint * > constrs;
            for (auto child: node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return Universe::UniverseJavaIntensionConstraintFactory::equiv(constrs);
        }
        case ExpressionType::OAND: {
            std::vector < Universe::IUniverseIntensionConstraint * > constrs;
            for (auto child: node->parameters) {
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
            std::vector < Universe::IUniverseIntensionConstraint * > constrs;
            for (auto child: node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return Universe::UniverseJavaIntensionConstraintFactory::disjunction(constrs);
        }
        case ExpressionType::OXOR: {
            std::vector < Universe::IUniverseIntensionConstraint * > constrs;
            for (auto child: node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return Universe::UniverseJavaIntensionConstraintFactory::parity(constrs);
        }
        case ExpressionType::OEQ: {
            std::vector < Universe::IUniverseIntensionConstraint * > constrs;
            for (auto child: node->parameters) {
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