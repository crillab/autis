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
 * @file AutisXcspCallback.cpp
 * @brief Defines the callback to be used with the XCSP3 parser to build a Universe solver.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../include/xcsp/AutisXcspCallback.hpp"

#include "../../../libs/exception/except/except.hpp"

#include "../../../libs/universe/universe/include/csp/intension/UniverseIntensionConstraintFactory.hpp"
#include "../../../libs/universe/universe/include/csp/intension/UniverseJavaIntensionConstraintFactory.hpp"

#ifdef INTEGER
#undef INTEGER
#endif

using namespace Autis;
using namespace Except;
using namespace std;
using namespace Universe;
using namespace XCSP3Core;

AutisXcspCallback::AutisXcspCallback(IUniverseCspSolver *solver,
        AbstractUniverseIntensionConstraintFactory *intensionFactory) :
        solver(solver),
        intensionFactory(intensionFactory) {
    intensionUsingString = false;
}

void AutisXcspCallback::beginInstance(InstanceType type) {
    optimization = type == XCSP3Core::COP;
}

AutisXcspCallback *AutisXcspCallback::newNativeInstance(IUniverseCspSolver *solver) {
    return new AutisXcspCallback(solver, new UniverseIntensionConstraintFactory());
}

AutisXcspCallback *AutisXcspCallback::newJavaInstance(IUniverseCspSolver *solver) {
    return new AutisXcspCallback(solver, new UniverseJavaIntensionConstraintFactory());
}

void AutisXcspCallback::buildVariableInteger(string id, int minValue, int maxValue) {
    solver->newVariable(id, minValue, maxValue);
}

void AutisXcspCallback::buildVariableInteger(string id, vector<int> &values) {
    solver->newVariable(id, values);
}

void AutisXcspCallback::buildConstraintAlldifferent(string id, vector<XVariable *> &list) {
    solver->addAllDifferent(toStringVector(list));
}

void AutisXcspCallback::buildConstraintIntension(string id, Tree *tree) {
    solver->addIntension(createIntension(tree->root));
}

void AutisXcspCallback::buildConstraintExtension(
        string id, XVariable *variable, vector<int> &tuples, bool support, bool hasStar) {
    if (hasStar) {
        throw UnsupportedOperationException("Starred tuples are not supported");
    }

    if (support) {
        solver->addSupport(variable->id, toBigIntegerVector(tuples));
    } else {
        solver->addConflicts(variable->id, toBigIntegerVector(tuples));
    }
}

void AutisXcspCallback::buildConstraintExtension(
        string id, vector<XVariable *> list, vector<vector<int>> &tuples, bool support, bool hasStar) {
    if (hasStar) {
        throw UnsupportedOperationException("Starred tuples are not supported");
    }

    if (support) {
        solver->addSupport(toStringVector(list), toBigIntegerMatrix(tuples));
    } else {
        solver->addConflicts(toStringVector(list), toBigIntegerMatrix(tuples));
    }
}

void AutisXcspCallback::buildConstraintSum(
        string id, vector<XVariable *> &list, XCondition &cond) {
    if (cond.operandType == XCSP3Core::INTEGER) {
        solver->addSum(toStringVector(list), operatorOf(cond), cond.val);

    } else if (cond.operandType == XCSP3Core::VARIABLE) {
        solver->addSum(toStringVector(list), operatorOf(cond), cond.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintSum(
        string id, vector<XVariable *> &list, vector<int> &coeffs, XCondition &cond) {
    if (cond.operandType == XCSP3Core::INTEGER) {
        solver->addSum(toStringVector(list), toBigIntegerVector(coeffs), operatorOf(cond), cond.val);

    } else if (cond.operandType == XCSP3Core::VARIABLE) {
        solver->addSum(toStringVector(list), toBigIntegerVector(coeffs), operatorOf(cond), cond.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintSum(
        string id, vector<XVariable *> &list, vector<XVariable *> &coeffs, XCondition &cond) {
    if (cond.operandType == XCSP3Core::INTEGER) {
        solver->addSumWithVariableCoefficients(
                toStringVector(list), toStringVector(coeffs), operatorOf(cond), cond.val);

    } else if (cond.operandType == XCSP3Core::VARIABLE) {
        solver->addSumWithVariableCoefficients(
                toStringVector(list), toStringVector(coeffs), operatorOf(cond), cond.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintSum(
        string id, vector<Tree *> &trees, XCondition &cond) {
    if (cond.operandType == XCSP3Core::INTEGER) {
        solver->addSumIntension(
                toIntensionConstraintVector(trees), operatorOf(cond), cond.val);

    } else if (cond.operandType == XCSP3Core::VARIABLE) {
        solver->addSumIntension(
                toIntensionConstraintVector(trees), operatorOf(cond), cond.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintSum(
        string id, vector<Tree *> &trees, vector<int> &coefs, XCondition &cond) {
    if (cond.operandType == XCSP3Core::INTEGER) {
        solver->addSumIntension(
                toIntensionConstraintVector(trees), toBigIntegerVector(coefs), operatorOf(cond), cond.val);

    } else if (cond.operandType == XCSP3Core::VARIABLE) {
        solver->addSumIntension(
                toIntensionConstraintVector(trees), toBigIntegerVector(coefs), operatorOf(cond), cond.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildObjectiveMaximize(
        ExpressionObjective type, vector<XVariable *> &list, vector<int> &coefs) {
    solver->maximizeSum(toStringVector(list), toBigIntegerVector(coefs));
}

UniverseRelationalOperator AutisXcspCallback::operatorOf(XCondition &cond) {
    switch (cond.op) {
        case XCSP3Core::LT:
            return UniverseRelationalOperator::LT;
        case XCSP3Core::LE:
            return UniverseRelationalOperator::LE;
        case XCSP3Core::EQ:
            return UniverseRelationalOperator::EQ;
        case XCSP3Core::NE:
            return UniverseRelationalOperator::NEQ;
        case XCSP3Core::GE:
            return UniverseRelationalOperator::GE;
        case XCSP3Core::GT:
            return UniverseRelationalOperator::GT;
        default:
            throw UnsupportedOperationException("Unsupported condition operator");
    }
}

IUniverseIntensionConstraint *AutisXcspCallback::createIntension(Node *node) {
    if (node->type == ExpressionType::ODECIMAL) {
        return intensionFactory->constant((long) ((NodeConstant *) node)->val);
    }

    if (node->type == ExpressionType::OVAR) {
        return intensionFactory->variable(((NodeVariable *) node)->var);
    }

    switch (node->type) {
        case ExpressionType::OABS: {
            auto child = createIntension(node->parameters[0]);
            return intensionFactory->abs(child);
        }
        
        case ExpressionType::OADD: {
            vector<IUniverseIntensionConstraint *> constrs;
            for (auto child : node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return intensionFactory->add(constrs);
        }

        case ExpressionType::ODIST: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->dist(child1, child2);
        }

        case ExpressionType::ODIV: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->div(child1, child2);
        }

        case ExpressionType::OMAX: {
            vector<IUniverseIntensionConstraint *> constrs;
            for (auto child : node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return intensionFactory->max(constrs);
        }

        case ExpressionType::OMIN: {
            vector<IUniverseIntensionConstraint *> constrs;
            for (auto child : node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return intensionFactory->min(constrs);
        }

        case ExpressionType::OMOD: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->mod(child1, child2);
        }

        case ExpressionType::OMUL: {
            vector<IUniverseIntensionConstraint *> constrs;
            for (auto child : node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return intensionFactory->mult(constrs);
        }

        case ExpressionType::ONEG: {
            auto child = createIntension(node->parameters[0]);
            return intensionFactory->neg(child);
        }

        case ExpressionType::OPOW: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->pow(child1, child2);
        }

        case ExpressionType::OSQR: {
            auto child = createIntension(node->parameters[0]);
            return intensionFactory->sqr(child);
        }

        case ExpressionType::OSUB: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->sub(child1, child2);
        }

        case ExpressionType::OIFF: {
            vector<IUniverseIntensionConstraint *> constrs;
            for (auto child : node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return intensionFactory->equiv(constrs);
        }

        case ExpressionType::OAND: {
            vector<IUniverseIntensionConstraint *> constrs;
            for (auto child : node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return intensionFactory->conjunction(constrs);
        }

        case ExpressionType::OIMP: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->impl(child1, child2);
        }

        case ExpressionType::ONOT: {
            auto child = createIntension(node->parameters[0]);
            return intensionFactory->negation(child);
        }

        case ExpressionType::OOR: {
            vector<IUniverseIntensionConstraint *> constrs;
            for (auto child : node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return intensionFactory->disjunction(constrs);
        }

        case ExpressionType::OXOR: {
            vector<IUniverseIntensionConstraint *> constrs;
            for (auto child : node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return intensionFactory->parity(constrs);
        }

        case ExpressionType::OLT: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->lt(child1, child2);
        }

        case ExpressionType::OLE: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->le(child1, child2);
        }

        case ExpressionType::OEQ: {
            vector<IUniverseIntensionConstraint *> constrs;
            for (auto child : node->parameters) {
                constrs.push_back(createIntension(child));
            }
            return intensionFactory->eq(constrs);
        }

        case ExpressionType::ONE: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->neq(child1, child2);
        }

        case ExpressionType::OGE: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->ge(child1, child2);
        }

        case ExpressionType::OGT: {
            auto child1 = createIntension(node->parameters[0]);
            auto child2 = createIntension(node->parameters[1]);
            return intensionFactory->gt(child1, child2);
        }

        default: {
            throw IllegalArgumentException("Unknown operator");
        }
    }
}

vector<string> AutisXcspCallback::toStringVector(const vector<XVariable *> &list) {
    vector<string> vars;
    for (auto variable : list) {
        vars.push_back(variable->id);
    }
    return vars;
}

vector<BigInteger> AutisXcspCallback::toBigIntegerVector(const vector<int> &integers) {
    vector<BigInteger> list;
    for (auto i : integers) {
        list.push_back(i);
    }
    return list;
}

vector<IUniverseIntensionConstraint *> AutisXcspCallback::toIntensionConstraintVector(
        const vector<Tree *> &expressions) {
    vector<IUniverseIntensionConstraint *> lists;
    for (auto expr : expressions) {
        lists.push_back(createIntension(expr->root));
    }
    return lists;
}

vector<vector<BigInteger>> AutisXcspCallback::toBigIntegerMatrix(const vector<vector<int>> &matrix) {
    vector<vector<BigInteger>> lists;
    for (auto i : matrix) {
        lists.push_back(toBigIntegerVector(i));
    }
    return lists;
}
