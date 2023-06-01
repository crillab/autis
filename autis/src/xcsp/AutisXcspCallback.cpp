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
                                     AbstractUniverseIntensionConstraintFactory *intensionFactory) : solver(solver),
                                                                                                     intensionFactory(intensionFactory) {
    intensionUsingString = false;
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
        //todo possible ?
        return;
    }

    if (support) {
        solver->addSupport(variable->id, toBigIntegerVector(tuples),hasStar);
    } else {
        solver->addConflicts(variable->id, toBigIntegerVector(tuples),hasStar);
    }
}

void AutisXcspCallback::buildConstraintExtension(
        string id, vector<XVariable *> list, vector<vector<int>> &tuples, bool support, bool hasStar) {
    lastTuples=tuples;

    if (support) {
        solver->addSupport(toStringVector(list), toBigIntegerMatrix(tuples),hasStar);
    } else {
        solver->addConflicts(toStringVector(list), toBigIntegerMatrix(tuples),hasStar);
    }
}


void AutisXcspCallback::buildConstraintExtensionAs(string id, vector<XVariable *> list, bool support, bool hasStar) {
    buildConstraintExtension(id,list,lastTuples,support,hasStar);
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
    if (type == ExpressionObjective::LEX_O) {
        throw UnsupportedOperationException("LEX objective are not supported");
    } else if (type == ExpressionObjective::MAXIMUM_O) {
        solver->maximizeMaximum(toStringVector(list), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::MINIMUM_O) {
        solver->maximizeMinimum(toStringVector(list), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::NVALUES_O) {
        solver->maximizeNValues(toStringVector(list), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::SUM_O) {
        solver->maximizeSum(toStringVector(list), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::PRODUCT_O) {
        solver->maximizeProduct(toStringVector(list), toBigIntegerVector(coefs));
    }
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
        return intensionFactory->constant((long)((NodeConstant *)node)->val);
    }

    if (node->type == ExpressionType::OVAR) {
        return intensionFactory->variable(((NodeVariable *)node)->var);
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
    for (auto &i : matrix) {
        lists.push_back(toBigIntegerVector(i));
    }
    return lists;
}

vector<vector<string>> AutisXcspCallback::toStringMatrix(const vector<vector<XCSP3Core::XVariable *>> &matrix) {
    vector<vector<string>> lists;
    for (auto &i : matrix) {
        lists.push_back(toStringVector(i));
    }
    return lists;
}

void AutisXcspCallback::buildConstraintPrimitive(std::string id, XCSP3Core::OrderType op, XCSP3Core::XVariable *x, int k,
                                                 XCSP3Core::XVariable *y) {
    solver->addPrimitive(x->id, UniverseArithmeticOperator::ADD, k, asRelationalOperator(op), y->id);
}

void AutisXcspCallback::buildConstraintPrimitive(std::string id, XCSP3Core::OrderType op, XCSP3Core::XVariable *x, int k) {
    solver->addPrimitive(x->id, asRelationalOperator(op), k);
}

void AutisXcspCallback::buildConstraintPrimitive(std::string id, XCSP3Core::XVariable *x, bool in, int min, int max) {
    solver->addPrimitive(x->id, in ? UniverseSetBelongingOperator::IN : UniverseSetBelongingOperator::NOT_IN, min, max);
}

void AutisXcspCallback::buildConstraintMult(std::string id, XCSP3Core::XVariable *x, XCSP3Core::XVariable *y,
                                            XCSP3Core::XVariable *z) {
    solver->addPrimitive(x->id, UniverseArithmeticOperator::MULT, y->id, UniverseRelationalOperator::EQ, z->id);
}

void AutisXcspCallback::buildConstraintAlldifferent(std::string id, vector<XCSP3Core::Tree *> &list) {
    solver->addAllDifferentIntension(toIntensionConstraintVector(list));
}

void AutisXcspCallback::buildConstraintAlldifferentExcept(std::string id, vector<XCSP3Core::XVariable *> &list,
                                                          vector<int> &except) {
    solver->addAllDifferent(toStringVector(list), toBigIntegerVector(except));
}

void AutisXcspCallback::buildConstraintAlldifferentList(std::string id, vector<std::vector<XCSP3Core::XVariable *>> &lists) {
    solver->addAllDifferentList(toStringMatrix(lists));
}

void AutisXcspCallback::buildConstraintAlldifferentMatrix(std::string id,
                                                          vector<std::vector<XCSP3Core::XVariable *>> &matrix) {
    solver->addAllDifferentMatrix(toStringMatrix(matrix));
}

void AutisXcspCallback::buildConstraintAllEqual(std::string id, vector<XCSP3Core::XVariable *> &list) {
    solver->addAllEqual(toStringVector(list));
}

void AutisXcspCallback::buildConstraintAllEqual(std::string id, vector<XCSP3Core::Tree *> &list) {
    solver->addAllEqualIntension(toIntensionConstraintVector(list));
}

void AutisXcspCallback::buildConstraintNotAllEqual(std::string id, vector<XCSP3Core::XVariable *> &list) {
    solver->addNotAllEqual(toStringVector(list));
}

void AutisXcspCallback::buildConstraintOrdered(std::string id, vector<XCSP3Core::XVariable *> &list,
                                               XCSP3Core::OrderType order) {
    solver->addOrdered(toStringVector(list), asRelationalOperator(order));
}

void AutisXcspCallback::buildConstraintOrdered(std::string id, vector<XCSP3Core::XVariable *> &list, vector<int> &lengths,
                                               XCSP3Core::OrderType order) {
    solver->addOrderedWithConstantLength(toStringVector(list), toBigIntegerVector(lengths),
                                         asRelationalOperator(order));
}

void AutisXcspCallback::buildConstraintLex(std::string id, vector<std::vector<XCSP3Core::XVariable *>> &lists,
                                           XCSP3Core::OrderType order) {
    solver->addLex(toStringMatrix(lists), asRelationalOperator(order));
}

void AutisXcspCallback::buildConstraintLexMatrix(std::string id, vector<std::vector<XCSP3Core::XVariable *>> &matrix,
                                                 XCSP3Core::OrderType order) {
    solver->addLexMatrix(toStringMatrix(matrix), asRelationalOperator(order));
}

void AutisXcspCallback::buildConstraintAtMost(std::string id, vector<XCSP3Core::XVariable *> &list, int value, int k) {
    solver->addAtMost(toStringVector(list), value, k);
}

void AutisXcspCallback::buildConstraintAtLeast(std::string id, vector<XCSP3Core::XVariable *> &list, int value, int k) {
    solver->addAtLeast(toStringVector(list), value, k);
}

void AutisXcspCallback::buildConstraintExactlyK(std::string id, vector<XCSP3Core::XVariable *> &list, int value, int k) {
    solver->addExactly(toStringVector(list), value, k);
}

void AutisXcspCallback::buildConstraintExactlyVariable(std::string id, vector<XCSP3Core::XVariable *> &list, int value,
                                                       XCSP3Core::XVariable *x) {
    solver->addExactly(toStringVector(list), value, x->id);
}

void AutisXcspCallback::buildConstraintAmong(std::string id, vector<XCSP3Core::XVariable *> &list, vector<int> &values,
                                             int k) {
    solver->addAmong(toStringVector(list), toBigIntegerVector(values), k);
}

void AutisXcspCallback::buildConstraintCount(std::string id, vector<XCSP3Core::XVariable *> &list, vector<int> &values,
                                             XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCountWithConstantValues(toStringVector(list), toBigIntegerVector(values), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCountWithConstantValues(toStringVector(list), toBigIntegerVector(values), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCount(std::string id, vector<XCSP3Core::XVariable *> &list,
                                             vector<XCSP3Core::XVariable *> &values, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCountWithVariableValues(toStringVector(list), toStringVector(list), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCountWithVariableValues(toStringVector(list), toStringVector(list), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCount(std::string id, vector<XCSP3Core::Tree *> &trees, vector<int> &values,
                                             XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCountIntensionWithConstantValues(toIntensionConstraintVector(trees), toBigIntegerVector(values), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCountIntensionWithConstantValues(toIntensionConstraintVector(trees), toBigIntegerVector(values), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintNValues(std::string id, vector<XCSP3Core::XVariable *> &list, vector<int> &except,
                                               XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addNValuesExcept(toStringVector(list), operatorOf(xc), xc.val, toBigIntegerVector(except));

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addNValuesExcept(toStringVector(list), operatorOf(xc), xc.var, toBigIntegerVector(except));

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintNValues(std::string id, vector<XCSP3Core::Tree *> &trees, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addNValuesIntension(toIntensionConstraintVector(trees), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addNValuesIntension(toIntensionConstraintVector(trees), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintNValues(std::string id, vector<XCSP3Core::XVariable *> &list, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addNValues(toStringVector(list), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addNValues(toStringVector(list), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCardinality(std::string id, vector<XCSP3Core::XVariable *> &list,
                                                   std::vector<int> values, vector<int> &occurs, bool closed) {
    solver->addCardinalityWithConstantValuesAndConstantCounts(toStringVector(list), toBigIntegerVector(values),
                                                              toBigIntegerVector(occurs), closed);
}

void AutisXcspCallback::buildConstraintCardinality(std::string id, vector<XCSP3Core::XVariable *> &list,
                                                   std::vector<int> values, vector<XCSP3Core::XVariable *> &occurs,
                                                   bool closed) {
    solver->addCardinalityWithConstantValuesAndVariableCounts(toStringVector(list), toBigIntegerVector(values),
                                                              toStringVector(occurs), closed);
}

void AutisXcspCallback::buildConstraintCardinality(std::string id, vector<XCSP3Core::XVariable *> &list,
                                                   std::vector<int> values, vector<XCSP3Core::XInterval> &occurs,
                                                   bool closed) {
    vector<BigInteger> occursMin(occurs.size());
    vector<BigInteger> occursMax(occurs.size());
    for (auto &interval : occurs) {
        occursMin.push_back(interval.min);
        occursMax.push_back(interval.max);
    }
    solver->addCardinalityWithConstantValuesAndConstantIntervalCounts(toStringVector(list), toBigIntegerVector(values),
                                                                      occursMin, occursMax, closed);
}

void AutisXcspCallback::buildConstraintCardinality(std::string id, vector<XCSP3Core::XVariable *> &list,
                                                   std::vector<XCSP3Core::XVariable *> values, vector<int> &occurs,
                                                   bool closed) {
    solver->addCardinalityWithVariableValuesAndConstantCounts(toStringVector(list), toStringVector(values),
                                                              toBigIntegerVector(occurs), closed);
}

void AutisXcspCallback::buildConstraintCardinality(std::string id, vector<XCSP3Core::XVariable *> &list,
                                                   std::vector<XCSP3Core::XVariable *> values,
                                                   vector<XCSP3Core::XVariable *> &occurs, bool closed) {
    solver->addCardinalityWithVariableValuesAndVariableCounts(toStringVector(list), toStringVector(values),
                                                              toStringVector(occurs), closed);
}

void AutisXcspCallback::buildConstraintCardinality(std::string id, vector<XCSP3Core::XVariable *> &list,
                                                   std::vector<XCSP3Core::XVariable *> values,
                                                   vector<XCSP3Core::XInterval> &occurs, bool closed) {
    vector<BigInteger> occursMin(occurs.size());
    vector<BigInteger> occursMax(occurs.size());
    for (auto &interval : occurs) {
        occursMin.push_back(interval.min);
        occursMax.push_back(interval.max);
    }
    solver->addCardinalityWithVariableValuesAndConstantIntervalCounts(toStringVector(list), toStringVector(values),
                                                                      occursMin, occursMax, closed);
}

void AutisXcspCallback::buildConstraintMinimum(std::string id, vector<XCSP3Core::XVariable *> &list, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addMinimum(toStringVector(list), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addMinimum(toStringVector(list), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintMinimum(std::string id, vector<XCSP3Core::Tree *> &list, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addMinimumIntension(toIntensionConstraintVector(list), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addMinimumIntension(toIntensionConstraintVector(list), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintMaximum(std::string id, vector<XCSP3Core::XVariable *> &list, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addMaximum(toStringVector(list), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addMaximum(toStringVector(list), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintMaximum(std::string id, vector<XCSP3Core::Tree *> &list, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addMaximumIntension(toIntensionConstraintVector(list), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addMaximumIntension(toIntensionConstraintVector(list), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintElement(std::string id, vector<XCSP3Core::XVariable *> &list, int value) {
    solver->addElement(toStringVector(list),Universe::UniverseRelationalOperator::EQ, value);
}

void AutisXcspCallback::buildConstraintElement(std::string id, vector<XCSP3Core::XVariable *> &list,
                                               XCSP3Core::XVariable *index, int startIndex, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addElement(toStringVector(list), startIndex, index->id, asRelationalOperator(xc.op), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addElement(toStringVector(list), startIndex, index->id,asRelationalOperator(xc.op), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintElement(std::string id, vector<std::vector<XCSP3Core::XVariable *>> &matrix,
                                               int startRowIndex, XCSP3Core::XVariable *rowIndex, int startColIndex,
                                               XCSP3Core::XVariable *colIndex, XCSP3Core::XVariable *value) {
    solver->addElementMatrix(toStringMatrix(matrix), startRowIndex, rowIndex->id, startColIndex, colIndex->id,Universe::UniverseRelationalOperator::EQ, value->id);
}



void AutisXcspCallback::buildConstraintElement(std::string id, vector<std::vector<XCSP3Core::XVariable *>> &matrix,
                                               int startRowIndex, XCSP3Core::XVariable *rowIndex, int startColIndex,
                                               XCSP3Core::XVariable *colIndex, int value) {
    solver->addElementMatrix(toStringMatrix(matrix), startRowIndex, rowIndex->id, startColIndex, colIndex->id, Universe::UniverseRelationalOperator::EQ,value);
}

void AutisXcspCallback::buildConstraintElement(std::string id, vector<std::vector<int>> &matrix, int startRowIndex,
                                               XCSP3Core::XVariable *rowIndex, int startColIndex,
                                               XCSP3Core::XVariable *colIndex, XCSP3Core::XVariable *value) {
    solver->addElementConstantMatrix(toBigIntegerMatrix(matrix), startRowIndex, rowIndex->id, startColIndex, colIndex->id, Universe::UniverseRelationalOperator::EQ,value->id);
}

void AutisXcspCallback::buildConstraintElement(std::string id, vector<XCSP3Core::XVariable *> &list,
                                               XCSP3Core::XVariable *value) {
    solver->addElement(toStringVector(list), Universe::UniverseRelationalOperator::EQ,value->id);
}

void AutisXcspCallback::buildConstraintChannel(std::string id, vector<XCSP3Core::XVariable *> &list, int startIndex) {
    solver->addChannel(toStringVector(list), startIndex);
}

void AutisXcspCallback::buildConstraintChannel(std::string id, vector<XCSP3Core::XVariable *> &list1, int startIndex1,
                                               vector<XCSP3Core::XVariable *> &list2, int startIndex2) {
    solver->addChannel(toStringVector(list1), startIndex1, toStringVector(list2), startIndex2);
}

void AutisXcspCallback::buildConstraintChannel(std::string id, vector<XCSP3Core::XVariable *> &list, int startIndex,
                                               XCSP3Core::XVariable *value) {
    solver->addChannel(toStringVector(list), startIndex, value->id);
}

void AutisXcspCallback::buildConstraintNoOverlap(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                 vector<int> &lengths, bool zeroIgnored) {
    solver->addNoOverlap(toStringVector(origins), toBigIntegerVector(lengths), zeroIgnored);
}

void AutisXcspCallback::buildConstraintNoOverlap(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                 vector<XCSP3Core::XVariable *> &lengths, bool zeroIgnored) {
    solver->addNoOverlapVariableLength(toStringVector(origins), toStringVector(lengths), zeroIgnored);
}

void AutisXcspCallback::buildConstraintNoOverlap(std::string id, vector<std::vector<XCSP3Core::XVariable *>> &origins,
                                                 vector<std::vector<int>> &lengths, bool zeroIgnored) {
    solver->addMultiDimensionalNoOverlap(toStringMatrix(origins), toBigIntegerMatrix(lengths), zeroIgnored);
}

void AutisXcspCallback::buildConstraintNoOverlap(std::string id, vector<std::vector<XCSP3Core::XVariable *>> &origins,
                                                 vector<std::vector<XCSP3Core::XVariable *>> &lengths,
                                                 bool zeroIgnored) {
    solver->addMultiDimensionalNoOverlapVariableLength(toStringMatrix(origins), toStringMatrix(lengths), zeroIgnored);
}

void AutisXcspCallback::buildConstraintCumulative(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                  vector<int> &lengths, vector<int> &heights, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCumulativeConstantLengthsConstantHeights(toStringVector(origins), toBigIntegerVector(lengths),
                                                            toBigIntegerVector(heights), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCumulativeConstantLengthsConstantHeights(toStringVector(origins), toBigIntegerVector(lengths),
                                                            toBigIntegerVector(heights), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCumulative(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                  vector<int> &lengths, vector<XCSP3Core::XVariable *> &varHeights,
                                                  XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCumulativeConstantLengthsVariableHeights(toStringVector(origins), toBigIntegerVector(lengths),
                                                            toStringVector(varHeights), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCumulativeConstantLengthsVariableHeights(toStringVector(origins), toBigIntegerVector(lengths),
                                                            toStringVector(varHeights), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCumulative(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                  vector<XCSP3Core::XVariable *> &lengths, vector<int> &heights,
                                                  XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCumulativeVariableLengthsConstantHeights(toStringVector(origins), toStringVector(lengths),
                                                            toBigIntegerVector(heights), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCumulativeVariableLengthsConstantHeights(toStringVector(origins), toStringVector(lengths),
                                                            toBigIntegerVector(heights), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCumulative(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                  vector<int> &lengths, vector<int> &heights,
                                                  vector<XCSP3Core::XVariable *> &ends, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCumulativeConstantLengthsConstantHeights(toStringVector(origins), toBigIntegerVector(lengths), toStringVector(ends),
                                                            toBigIntegerVector(heights), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCumulativeConstantLengthsConstantHeights(toStringVector(origins), toBigIntegerVector(lengths), toStringVector(ends),
                                                            toBigIntegerVector(heights), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCumulative(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                  vector<int> &lengths, vector<XCSP3Core::XVariable *> &varHeights,
                                                  vector<XCSP3Core::XVariable *> &ends, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCumulativeConstantLengthsVariableHeights(toStringVector(origins), toBigIntegerVector(lengths), toStringVector(ends),
                                                            toStringVector(varHeights), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCumulativeConstantLengthsVariableHeights(toStringVector(origins), toBigIntegerVector(lengths), toStringVector(ends),
                                                            toStringVector(varHeights), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCumulative(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                  vector<XCSP3Core::XVariable *> &lengths,
                                                  vector<XCSP3Core::XVariable *> &heights,
                                                  vector<XCSP3Core::XVariable *> &ends, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCumulativeVariableLengthsVariableHeights(toStringVector(origins), toStringVector(lengths), toStringVector(ends),
                                                            toStringVector(heights), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCumulativeVariableLengthsVariableHeights(toStringVector(origins), toStringVector(lengths), toStringVector(ends),
                                                            toStringVector(heights), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCumulative(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                  vector<XCSP3Core::XVariable *> &lengths, vector<int> &heights,
                                                  vector<XCSP3Core::XVariable *> &ends, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCumulativeVariableLengthsConstantHeights(toStringVector(origins), toStringVector(lengths), toStringVector(ends),
                                                            toBigIntegerVector(heights), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCumulativeVariableLengthsConstantHeights(toStringVector(origins), toStringVector(lengths), toStringVector(ends),
                                                            toBigIntegerVector(heights), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintCumulative(std::string id, vector<XCSP3Core::XVariable *> &origins,
                                                  vector<XCSP3Core::XVariable *> &lengths,
                                                  vector<XCSP3Core::XVariable *> &heights, XCondition &xc) {
    if (xc.operandType == XCSP3Core::INTEGER) {
        solver->addCumulativeVariableLengthsVariableHeights(toStringVector(origins), toStringVector(lengths),
                                                            toStringVector(heights), operatorOf(xc), xc.val);

    } else if (xc.operandType == XCSP3Core::VARIABLE) {
        solver->addCumulativeVariableLengthsVariableHeights(toStringVector(origins), toStringVector(lengths),
                                                            toStringVector(heights), operatorOf(xc), xc.var);

    } else {
        throw UnsupportedOperationException("Unsupported condition type");
    }
}

void AutisXcspCallback::buildConstraintInstantiation(std::string id, vector<XCSP3Core::XVariable *> &list,
                                                     vector<int> &values) {
    solver->addInstantiation(toStringVector(list), toBigIntegerVector(values));
}

void AutisXcspCallback::buildConstraintClause(std::string id, vector<XCSP3Core::XVariable *> &positive,
                                              vector<XCSP3Core::XVariable *> &negative) {
    solver->addClause(toStringVector(positive), toStringVector(negative));
}

void AutisXcspCallback::buildObjectiveMinimizeVariable(XCSP3Core::XVariable *x) {
    solver->minimizeVariable(x->id);
}

void AutisXcspCallback::buildObjectiveMaximizeVariable(XCSP3Core::XVariable *x) {
    solver->maximizeVariable(x->id);
}

void AutisXcspCallback::buildObjectiveMinimize(XCSP3Core::ExpressionObjective type, vector<XCSP3Core::XVariable *> &list,
                                               vector<int> &coefs) {
    if (type == ExpressionObjective::LEX_O) {
        throw UnsupportedOperationException("LEX objective are not supported");
    } else if (type == ExpressionObjective::MAXIMUM_O) {
        solver->minimizeMaximum(toStringVector(list), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::MINIMUM_O) {
        solver->minimizeMinimum(toStringVector(list), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::NVALUES_O) {
        solver->minimizeNValues(toStringVector(list), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::SUM_O) {
        solver->minimizeSum(toStringVector(list), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::PRODUCT_O) {
        solver->minimizeProduct(toStringVector(list), toBigIntegerVector(coefs));
    }
}

void AutisXcspCallback::buildObjectiveMinimize(XCSP3Core::ExpressionObjective type, vector<XCSP3Core::XVariable *> &list) {
    if (type == ExpressionObjective::LEX_O) {
        throw UnsupportedOperationException("LEX objective are not supported");
    } else if (type == ExpressionObjective::MAXIMUM_O) {
        solver->minimizeMaximum(toStringVector(list));
    } else if (type == ExpressionObjective::MINIMUM_O) {
        solver->minimizeMinimum(toStringVector(list));
    } else if (type == ExpressionObjective::NVALUES_O) {
        solver->minimizeNValues(toStringVector(list));
    } else if (type == ExpressionObjective::SUM_O) {
        solver->minimizeSum(toStringVector(list));
    } else if (type == ExpressionObjective::PRODUCT_O) {
        solver->minimizeProduct(toStringVector(list));
    }
}

void AutisXcspCallback::buildObjectiveMaximize(XCSP3Core::ExpressionObjective type, vector<XCSP3Core::XVariable *> &list) {
    if (type == ExpressionObjective::LEX_O) {
        throw UnsupportedOperationException("LEX objective are not supported");
    } else if (type == ExpressionObjective::MAXIMUM_O) {
        solver->maximizeMaximum(toStringVector(list));
    } else if (type == ExpressionObjective::MINIMUM_O) {
        solver->maximizeMinimum(toStringVector(list));
    } else if (type == ExpressionObjective::NVALUES_O) {
        solver->maximizeNValues(toStringVector(list));
    } else if (type == ExpressionObjective::SUM_O) {
        solver->maximizeSum(toStringVector(list));
    } else if (type == ExpressionObjective::PRODUCT_O) {
        solver->maximizeProduct(toStringVector(list));
    }
}

void AutisXcspCallback::buildObjectiveMinimize(XCSP3Core::ExpressionObjective type, vector<XCSP3Core::Tree *> &trees,
                                               vector<int> &coefs) {
    if (type == ExpressionObjective::LEX_O) {
        throw UnsupportedOperationException("LEX objective are not supported");
    } else if (type == ExpressionObjective::MAXIMUM_O) {
        solver->minimizeExpressionMaximum(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::MINIMUM_O) {
        solver->minimizeExpressionMinimum(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::NVALUES_O) {
        solver->minimizeExpressionNValues(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::SUM_O) {
        solver->minimizeExpressionSum(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::PRODUCT_O) {
        solver->minimizeExpressionProduct(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    }
}

void AutisXcspCallback::buildObjectiveMaximize(XCSP3Core::ExpressionObjective type, vector<XCSP3Core::Tree *> &trees,
                                               vector<int> &coefs) {
    if (type == ExpressionObjective::LEX_O) {
        throw UnsupportedOperationException("LEX objective are not supported");
    } else if (type == ExpressionObjective::MAXIMUM_O) {
        solver->maximizeExpressionMaximum(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::MINIMUM_O) {
        solver->maximizeExpressionMinimum(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::NVALUES_O) {
        solver->maximizeExpressionNValues(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::SUM_O) {
        solver->maximizeExpressionSum(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    } else if (type == ExpressionObjective::PRODUCT_O) {
        solver->maximizeExpressionProduct(toIntensionConstraintVector(trees), toBigIntegerVector(coefs));
    }
}

void AutisXcspCallback::buildObjectiveMinimize(XCSP3Core::ExpressionObjective type, vector<XCSP3Core::Tree *> &trees) {
    if (type == ExpressionObjective::LEX_O) {
        throw UnsupportedOperationException("LEX objective are not supported");
    } else if (type == ExpressionObjective::MAXIMUM_O) {
        solver->minimizeExpressionMaximum(toIntensionConstraintVector(trees));
    } else if (type == ExpressionObjective::MINIMUM_O) {
        solver->minimizeExpressionMinimum(toIntensionConstraintVector(trees));
    } else if (type == ExpressionObjective::NVALUES_O) {
        solver->minimizeExpressionNValues(toIntensionConstraintVector(trees));
    } else if (type == ExpressionObjective::SUM_O) {
        solver->minimizeExpressionSum(toIntensionConstraintVector(trees));
    } else if (type == ExpressionObjective::PRODUCT_O) {
        solver->minimizeExpressionProduct(toIntensionConstraintVector(trees));
    }
}

void AutisXcspCallback::buildObjectiveMaximize(XCSP3Core::ExpressionObjective type, vector<XCSP3Core::Tree *> &trees) {
    if (type == ExpressionObjective::LEX_O) {
        throw UnsupportedOperationException("LEX objective are not supported");
    } else if (type == ExpressionObjective::MAXIMUM_O) {
        solver->maximizeExpressionMaximum(toIntensionConstraintVector(trees));
    } else if (type == ExpressionObjective::MINIMUM_O) {
        solver->maximizeExpressionMinimum(toIntensionConstraintVector(trees));
    } else if (type == ExpressionObjective::NVALUES_O) {
        solver->maximizeExpressionNValues(toIntensionConstraintVector(trees));
    } else if (type == ExpressionObjective::SUM_O) {
        solver->maximizeExpressionSum(toIntensionConstraintVector(trees));
    } else if (type == ExpressionObjective::PRODUCT_O) {
        solver->maximizeExpressionProduct(toIntensionConstraintVector(trees));
    }
}

Universe::UniverseRelationalOperator AutisXcspCallback::asRelationalOperator(XCSP3Core::OrderType type) {
    switch (type) {
        case XCSP3Core::OrderType::EQ:
            return UniverseRelationalOperator::EQ;
        case XCSP3Core::OrderType::LE:
            return UniverseRelationalOperator::LE;
        case XCSP3Core::OrderType::LT:
            return UniverseRelationalOperator::LT;
        case XCSP3Core::OrderType::GE:
            return UniverseRelationalOperator::GE;
        case XCSP3Core::OrderType::GT:
            return UniverseRelationalOperator::GT;
        case XCSP3Core::OrderType::NE:
            return UniverseRelationalOperator::NEQ;
        default:
            throw IllegalArgumentException("Unknown operator");
    }
}
