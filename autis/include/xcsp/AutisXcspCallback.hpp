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
 * @file AutisXcspCallback.hpp
 * @brief Defines the callback to be used with the XCSP3 parser to build a Universe solver.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef AUTIS_AUTISXCSPCALLBACK_HPP
#define AUTIS_AUTISXCSPCALLBACK_HPP

#include "../../../libs/universe/universe/include/csp/IUniverseCspSolver.hpp"
#include "../../../libs/universe/universe/include/csp/intension/AbstractUniverseIntensionConstraintFactory.hpp"
#include "XCSP3CoreCallbacks.h"

namespace Autis {

/**
 * The AutisXcspCallback is the callback to be used with the XCSP3 parser to build a
 * Universe solver.
 */
class AutisXcspCallback : public XCSP3Core::XCSP3CoreCallbacks {
   private:
    /**
     * The solver to feed while parsing.
     */
    Universe::IUniverseCspSolver *solver;

    /**
     * The factory to use to create intension constraints.
     */
    Universe::AbstractUniverseIntensionConstraintFactory *intensionFactory;

    bool optimization;

    std::vector<std::vector<int>> lastTuples;

   private:
    /**
     * Creates a new AutisXcspCallback.
     *
     * @param solver The solver to feed while parsing.
     * @param intensionFactory The factory to use to create intension constraints.
     */
    explicit AutisXcspCallback(Universe::IUniverseCspSolver *solver,
                               Universe::AbstractUniverseIntensionConstraintFactory *intensionFactory);

   public:
    /**
     * Creates a new AutisXcspCallback for feeding native solvers.
     *
     * @param solver The solver to feed while parsing.
     * @param intensionFactory The factory to use to create intension constraints.
     *
     * @return The created callback.
     */
    static AutisXcspCallback *newNativeInstance(Universe::IUniverseCspSolver *solver);

    /**
     * Creates a new AutisXcspCallback for feeding java solvers.
     *
     * @param solver The solver to feed while parsing.
     * @param intensionFactory The factory to use to create intension constraints.
     *
     * @return The created callback.
     */
    static AutisXcspCallback *newJavaInstance(Universe::IUniverseCspSolver *solver);

    /**
     * Destroys this AutisXcspCallback.
     */
    virtual ~AutisXcspCallback() = default;

    /**
     * The callback function related to an integer variable with a range domain
     * See http://xcsp.org/specifications/integers
     *
     * Example: <var id="bar"> 0..6 </var>
     *
     * @param id the id (name) of the group
     * @param minValue the minimum value in the range
     * @param maxValue the maxnimum value in the range
     */
    void buildVariableInteger(std::string id, int minValue, int maxValue) override;

    /**
     * The callback function related to an integer variable with a domain consisting in a sequence of integers
     * See http://xcsp.org/specifications/integers
     *
     * Example <var id="bar"> 1 3 5 10 </var>
     *
     * @param id the id (name) of the group
     * @param values the set of values in the domain
     */
    void buildVariableInteger(std::string id, std::vector<int> &values) override;

    /**
     * All callbacks related to constraints.
     * Note that the variables related to a constraint are #XCSP3Core::XVariable instances. A XCSP3Core::XVariable contains an id and
     * the related domain.
     * (see XCSP3Variable.h)
     *
     */

    /**
     * The callback function related to an constraint in extension
     * See http://xcsp.org/specifications/extension
     *
     * Example:
     * <extension>
     *   <list> y1 y2 y3 y4 </list>
     *   <conflicts> (1,2,3,4)(3,1,3,4) </conflicts>
     * </extension>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param tuples the set of tuples in the constraint
     * @param support  support or conflicts?
     * @param hasStar is the tuples contain star values?
     */
    void buildConstraintExtension(std::string id, std::vector<XCSP3Core::XVariable *> list, std::vector<std::vector<int>> &tuples, bool support, bool hasStar) override;

    /*
     * The callback function related to an constraint in extension
     * Note that this callback is related to an unary constraint
     * See http://xcsp.org/specifications/extension
     * Example:
     * <extension>
     *   <list> x </list>
     *   <conflicts> 2 6 </conflicts>
     * </extension>
     *
     * @param id the id (name) of the constraint
     * @param variable the variable
     * @param tuples the set of tuple (here just set of ints)
     * @param support  support or conflicts?
     * @param hasStar is the tuples contain star values?
     */
    void buildConstraintExtension(std::string id, XCSP3Core::XVariable *variable, std::vector<int> &tuples, bool support, bool hasStar) override;

    /**
     * The callback function related to a constraint in intension
     * Only called if intensionUsingString is set to false (otherwise the previous function is called
     * See http://xcsp.org/specifications/intension
     * Example:
     * <intension> eq(add(x,y),z) </intension>
     *
     * @param id the id (name) of the constraint
     * @param tree the canonized form related to the tree
     */
    void buildConstraintIntension(std::string id, XCSP3Core::Tree *tree) override;

    /**
     * If  #recognizeSpecialIntensionCases is enabled (this is the case by default)
     * intensional constraint of the form : x +-k op y is recognized.
     * If such a intensional constraint is recognized, a callback to this function is done and not to  #buildConstraintIntension
     *
     * @param id the id (name) of the constraint
     * @param op the order LE, LT...
     * @param x the variable
     * @param k the constant
     * @param y the other variable
     */
    void buildConstraintPrimitive(std::string id, XCSP3Core::OrderType op, XCSP3Core::XVariable *x, int k, XCSP3Core::XVariable *y) override;

    /**
     * If  #recognizeSpecialIntensionCases is enabled (this is the case by default)
     * intensional constraint of the form : x op k  is recognized.
     * If such a intensional constraint is recognized, a callback to this function is done and not to  #buildConstraintIntension
     *
     * @param id the id (name) of the constraint
     * @param op the order LE or GE (EQ and NE are performed using #buildConstrantExtension)
     * @param x the variable
     * @param k the constant
     */
    void buildConstraintPrimitive(std::string id, XCSP3Core::OrderType op, XCSP3Core::XVariable *x, int k) override;

    /**
     * If  #recognizeSpecialIntensionCases is enabled (this is the case by default)
     * intensional constraint of the form : x in/notin [min max] are recognized
     * If such a intensional constraint is recognized, a callback to this function is done and not to  #buildConstraintIntension
     *
     * @param id the id (name) of the constraint
     * @param x the variable
     * @param in true if x is in this interval
     * @param min the constant
     * @param max the constant
     *
     */
    void buildConstraintPrimitive(std::string id, XCSP3Core::XVariable *x, bool in, int min, int max) override;

    /**
     * If  #recognizeSpecialIntensionCases is enabled (this is the case by default)
     * intensional constraint of the form : x*y=z are recognized
     * If such a intensional constraint is recognized, a callback to this function is done and not to  #buildConstraintIntension
     *
     * @param id the id (name) of the constraint
     * @param x,y,z  the variables
     */
    void buildConstraintMult(std::string id, XCSP3Core::XVariable *x, XCSP3Core::XVariable *y, XCSP3Core::XVariable *z) override;

    /**
     * The callback function related to a alldifferent constraint.
     * See http://xcsp.org/specifications/alldifferent
     *
     * Example:
     * <allDifferent>
     *   x1 x2 x3 x4 x5
     * </allDifferent>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     */
    void buildConstraintAlldifferent(std::string id, std::vector<XCSP3Core::XVariable *> &list) override;

    /**
     * The callback function related to a alldifferent constraint with expression
     * See http://xcsp.org/specifications/alldifferent
     *
     * Example:
     * <allDifferent>
     *   add(q[0],0) add(q[1],1) add(q[2],2) add(q[3],3) add(q[4],4) add(q[5],5) add(q[6],6) add(q[7],7)
     * </allDifferent>
     *
     * @param id the id (name) of the constraint
     * @param list the trees of the constraint
     */
    void buildConstraintAlldifferent(std::string id, std::vector<XCSP3Core::Tree *> &list) override;

    /**
     * The callback function related to a alldifferent with some excepted values constraint
     * See http://xcsp.org/specifications/alldifferent
     *
     * Example:
     * <allDifferent>
     *   x1 x2 x3 x4 x5
     *   <except>0</except>
     * </allDifferent>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param except the set of excepted values
     */
    void buildConstraintAlldifferentExcept(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &except) override;

    /**
     * The callback function related to a alldifferent  list constraint
     * See http://xcsp.org/specifications/alldifferent
     *
     * Example:
     * <allDifferent id="c1">
     *    <list> x1 x2 x3 x4 </list>
     *    <list> y1 y2 y3 y4 </list>
     * </allDifferent>
     *
     * @param id the id (name) of the constraint
     * @param lists the set of lists (not the scope, a variable may appear at different place!)
     */
    void buildConstraintAlldifferentList(std::string id, std::vector<std::vector<XCSP3Core::XVariable *>> &lists) override;

    /**
     * The callback function related to a alldifferent  matrix constraint
     * See http://xcsp.org/specifications/alldifferent
     *
     * Example:
     * <allDifferent id="c1">
     *    <matrix>
     *     (x1,x2,x3,x4,x5)
     *     (y1,y2,y3,y4,y5)
     *     (z1,z2,z3,z4,z5)
     *    </matrix>
     * </allDifferent>
     *
     * @param id the id (name) of the constraint
     * @param matrix the matrix (not the scope, a variable may appear at different place!)
     */
    void buildConstraintAlldifferentMatrix(std::string id, std::vector<std::vector<XCSP3Core::XVariable *>> &matrix) override;

    /**
     * The callback function related to a allequal constraint
     * See http://xcsp.org/specifications/allEqual
     *
     * Example:
     * <allEqual>
     *  x1 x2 x3 x4 x5
     * </allEqual>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     *
     */
    void buildConstraintAllEqual(std::string id, std::vector<XCSP3Core::XVariable *> &list) override;

    /**
     * The callback function related to a allEqual constraint with expression
     * See http://xcsp.org/specifications/allEqual
     *
     * Example:
     * <allEqual>
     *   add(q[0],0) add(q[1],1) add(q[2],2) add(q[3],3) add(q[4],4) add(q[5],5) add(q[6],6) add(q[7],7)
     * </allEqual>
     *
     * @param id the id (name) of the constraint
     * @param list the trees of the constraint
     */
    void buildConstraintAllEqual(std::string id, std::vector<XCSP3Core::Tree *> &list) override;

    /**
     * The callback function related to a not all equal constraint
     * This is a special case of nvalues constraint
     * Recognized if #recognizeNValuesCases is enabled (this is the case by default)
     * See http://xcsp.org/specifications/nValues
     *
     * Example:
     * <nValues id="c1">
     *   <list> x1 x2 x3 x4 </list>
     *   <condition> (gt,1) </condition>
     * </nValues>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     */
    void buildConstraintNotAllEqual(std::string id, std::vector<XCSP3Core::XVariable *> &list) override;

    /**
     * The callback function related to an ordered constraint
     * See http://xcsp.org/specifications/ordered
     *
     * Ordered is LE, LT, GE, GT... See XCSP3Core::OrderType in XCSPConstants.h
     *
     * Example:
     * <ordered>
     *   <list> x1 x2 x3 x4 </list>
     *   <operator> lt </operator>
     * </ordered>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param order the order LT, LE...
     */
    void buildConstraintOrdered(std::string id, std::vector<XCSP3Core::XVariable *> &list, XCSP3Core::OrderType order) override;

    /**
     * The callback function related to an ordered constraint
     * See http://xcsp.org/specifications/ordered
     *
     * Ordered is LE, LT, GE, GT... See XCSP3Core::OrderType in XCSPConstants.h
     *
     * Example:
     * <ordered>
     *   <list> x1 x2 x3 x4 </list>
     *   <operator> lt </operator>
     * </ordered>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param order the order LT, LE...
     */
    void buildConstraintOrdered(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &lengths, XCSP3Core::OrderType order) override;

    /**
     * The callback function related to an ordered list constraint (this is a lex constraint)
     * See http://xcsp.org/specifications/ordered
     *
     *
     * Example:
     * <ordered>
     *   <list> x1 x2 x3 x4 </list>
     *   <list> y1 y2 y3 y4 </list>
     *   <operator> lt </operator>
     * </ordered>
     *
     * @param id  the id (name) of the constraint
     * @param lists the set of lists (not the scope, a variable may appear at different place!)
     * @param order the order LT, LE...
     */
    void buildConstraintLex(std::string id, std::vector<std::vector<XCSP3Core::XVariable *>> &lists, XCSP3Core::OrderType order) override;

    /**
     * The callback function related to an ordered matrix constraint
     * See http://xcsp.org/specifications/ordered
     *
     *
     * Example:
     * <ordered>
     *   <matrix>
     *     (z1,z2,z3)
     *     (z4,z5,z6)
     *     (z7,z8,z9)
     *   </matrix>
     *   <operator> lt </operator>
     * </ordered>
     *
     * @param id the id (name) of the constraint
     * @param matrix the matrix (not the scope, a variable may appear at different place!)
     * @param order the order LT, LE...
     */
    void buildConstraintLexMatrix(std::string id, std::vector<std::vector<XCSP3Core::XVariable *>> &matrix, XCSP3Core::OrderType order) override;

    //--------------------------------------------------------------------------------------
    // Summing and counting constraints
    //--------------------------------------------------------------------------------------

    /**
     * The callback function related to an sum constraint
     * See http://xcsp.org/specifications/sum
     *
     * XCSP3Core::XCondition is an object with on XCSP3Core::OrderType (LE, LT...) an operandType (INTEGER, INTERVAL or VARIABLE)
     * depending the value of this field, either val (if operandType is INTEGER), min/max (INTERVAL) or var (VARIABLE)
     * is useful.
     * Example:
     * <sum>
     *   <list> x1 x2 x3 </list>
     *   <coeffs> 1 2 3 </coeffs>
     *   <condition> (gt,y) </condition>
     * </sum>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param coeffs the coefficients (here int)
     * @param cond the condition (See XCSP3Core::XCondition object)
     */
    void buildConstraintSum(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &coeffs, XCSP3Core::XCondition &cond) override;

    /**
     * The callback function related to an sum constraint with all coefs are equal to one
     * See http://xcsp.org/specifications/sum
     *
     * Example:
     * <sum>
     *   <list> x1 x2 x3 </list>
     *   <condition> (gt,y) </condition>
     * </sum>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param cond the condition (See XCSP3Core::XCondition object)
     */
    void buildConstraintSum(std::string id, std::vector<XCSP3Core::XVariable *> &list, XCSP3Core::XCondition &cond) override;

    /**
     * The callback function related to a sum constraint with all coefs are variables
     * See http://xcsp.org/specifications/sum
     *
     * Example:
     * <sum>
     *   <list> x1 x2 x3 </list>
     *   <coeffs> y1 y2 y3 </coeffs>
     *   <condition> (gt,y) </condition>
     * </sum>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param coeffs the coefficients (here XCSP3Core::XVariable)
     * @param cond the condition (See XCSP3Core::XCondition object)
     */
    void buildConstraintSum(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<XCSP3Core::XVariable *> &coeffs, XCSP3Core::XCondition &cond) override;

    /**
     * The callback function related to a sum constraint with trees in list
     *
     * Example:
     * <sum>
     *   <list>or(eq(x[5],0),eq(x[7],0)) or(eq(x[1],0),eq(x[2],0),eq(x[8],0)) or(eq(x[0],0),eq(x[3],0),eq(x[4],0),eq(x[6],0),eq(x[9],0))</list>
     *   <condition> (gt,y) </condition>
     * </sum>
     *
     * @param id the id (name) of the constraint
     * @param list the different trees
     * @param cond the condition (See XCSP3Core::XCondition object)
     */
    void buildConstraintSum(std::string id, std::vector<XCSP3Core::Tree *> &trees, XCSP3Core::XCondition &cond) override;

    /**
     * The callback function related to a sum constraint with trees in list
     *
     * Example:
     * <sum>
     *   <list>or(eq(x[5],0),eq(x[7],0)) or(eq(x[1],0),eq(x[2],0),eq(x[8],0)) or(eq(x[0],0),eq(x[3],0),eq(x[4],0),eq(x[6],0),eq(x[9],0))</list>
     *   <coeffs>1 2 3</coeffs>
     *   <condition> (gt,y) </condition>
     * </sum>
     *
     * @param id the id (name) of the constraint
     * @param list the different trees
     * @param coefs the coefs.
     * @param cond the condition (See XCSP3Core::XCondition object)
     */
    void buildConstraintSum(std::string id, std::vector<XCSP3Core::Tree *> &trees, std::vector<int> &coefs, XCSP3Core::XCondition &cond) override;

    /**
     * The callback function related to a atmost constraint
     * This is a special count constraint
     * This callback is called if #recognizeSpecialCountCases is enabled (this is the case by default)
     * See http://xcsp.org/specifications/count
     *
     *
     * Example:
     * <count id="c4">
     *   <list> y1 y2 y3 y4 </list>
     *   <values> 0 </values>
     *   <condition> (le,2) </condition>
     * </count>
     *
     * Here at most 2 variables from y1...y4 can have value 0
     *
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param value the value
     * @param k the maximum number of variables that can take the value
     */
    void buildConstraintAtMost(std::string id, std::vector<XCSP3Core::XVariable *> &list, int value, int k) override;

    /**
     * The callback function related to a atleast constraint
     * This is a special count constraint
     * This callback is called if #recognizeSpecialCountCases is enabled
     * See http://xcsp.org/specifications/count
     *
     *
     * Example:
     * <count id="c3">
     *    <list> x1 x2 x3 x4 x5 </list>
     *    <values> 1 </values>
     *    <condition> (ge,3) </condition>
     * </count>
     *
     * Here at least 3 variables from x1...x5 must have value 1
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param value the value
     * @param k the minimum number of variables that can take the value
     */
    void buildConstraintAtLeast(std::string id, std::vector<XCSP3Core::XVariable *> &list, int value, int k) override;

    /**
     * The callback function related to a exactly k  constraint
     * This is a special count constraint
     * This callback is called if #recognizeSpecialCountCases is enabled
     * See http://xcsp.org/specifications/count
     *
     *
     * Example:
     * <count id="c5">
     *    <list> z1 z2 z3  Z4</list>
     *    <values> 0 </values>
     *    <condition> (eq,2) </condition>
     * </count>
     * Here exactly 2 variables from z1...z4 must have value 0
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param value the value
     * @param k the exact number of variables that can take the value
     */
    void buildConstraintExactlyK(std::string id, std::vector<XCSP3Core::XVariable *> &list, int value, int k) override;

    /**
     * The callback function related to a exactly k variable constraint
     * This is a special count constraint
     * This callback is called if #recognizeSpecialCountCases is enabled
     * See http://xcsp.org/specifications/count
     *
     *
     * Example:
     * <count id="c5">  <!-- exactly -->
     *    <list> z1 z2 z3  Z4</list>
     *    <values> 0 </values>
     *    <condition> (eq,z5) </condition>
     * </count>
     * Here exactly z5 variables from z1...z4 must have value 0
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param value the value
     * @param x the exact number of variables that can take the value (here it is a variable)
     */
    void buildConstraintExactlyVariable(std::string id, std::vector<XCSP3Core::XVariable *> &list, int value, XCSP3Core::XVariable *x) override;

    /**
     * The callback function related to a among constraint
     * This is a special count constraint
     * This callback is called if #recognizeSpecialCountCases is enabled
     * See http://xcsp.org/specifications/count
     *
     *
     * Example:
     * <count id="c2">
     *   <list> w1 w2 w3 w4 </list>
     *   <values> 1 5 8 </values>
     *   <condition> (eq,k2) </condition>
     * </count>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param value the value
     * @param k
     */
    void buildConstraintAmong(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &values, int k) override;

    /**
     * The callback function related to a count constraint with integer values
     * See http://xcsp.org/specifications/count
     * Example:
     * <count id="c1">
     *     <list> v1 v2 v3 v4 </list>
     *     <values> 2 4 </values>
     *     <condition> (ne,k1) </condition>
     * </count>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param value the set of  values (here set of ints)
     * @param k the  number of variables
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintCount(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &values, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a count constraint with integer variables
     * See http://xcsp.org/specifications/count
     * Example:
     * <count id="c1">
     *     <list> v1 v2 v3 v4 </list>
     *     <values> x1 x2 </values>
     *     <condition> (ne,k1) </condition>
     * </count>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param value the set of  values (here set of variables)
     * @param k the  number of variables
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintCount(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<XCSP3Core::XVariable *> &values, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a count constraint with expressions
     * See http://xcsp.org/specifications/count
     * Example:
     * <count id="c1">
     *     <list> eq(x,1) ne(z,2) </list>
     *     <values> 2 </values>
     *     <condition> (ne,k1) </condition>
     * </count>
     *
     * @param id the id (name) of the constraint
     * @param trees the trees
     * @param value the set of  integer values
     * @param k the  number of variables
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintCount(std::string id, std::vector<XCSP3Core::Tree *> &trees, std::vector<int> &values, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a nValues constraint with exception
     * See http://xcsp.org/specifications/nValues
     * Example:
     * <nValues id="c3">
     *   <list> z1 z2 z3 z4 </list>
     *    <except> 0 </except>
     *    <condition> (eq,2) </condition>
     * </nValues>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param except the set of excepted values
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintNValues(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &except, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a nValues constraint with expressions
     * See http://xcsp.org/specifications/nValues
     * Example:
     * <nValues id="c3">
     *   <list> eq(z1,5) ne(z2,4) </list>
     *    <condition> (eq,2) </condition>
     * </nValues>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param except the set of excepted values
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintNValues(std::string id, std::vector<XCSP3Core::Tree *> &trees, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a nValues constraint with exception
     * See http://xcsp.org/specifications/nValues
     * Example:
     * <nValues id="c3">
     *   <list> z1 z2 z3 z4 </list>
     *   <condition> (eq,2) </condition>
     * </nValues>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintNValues(std::string id, std::vector<XCSP3Core::XVariable *> &list, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a cardinality constraint with int values and int occurs
     * See http://xcsp.org/specifications/cardinality
     *
     * Example:
     * <cardinality>
     *   <list> x1 x2 x3 x4 </list>
     *   <values> 2 5 10 </values>
     *   <occurs> 1 2 3 </occurs>
     * </cardinality>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param values the set of values (here int)
     * @param occurs the number of occurences (here int)
     * @param closed is the constraint is closed
     */
    void buildConstraintCardinality(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> values, std::vector<int> &occurs, bool closed) override;

    //
    /**
     * The callback function related to a cardinality constraint with int values and variable occurs
     * See http://xcsp.org/specifications/cardinality
     *
     * Example:
     * <cardinality>
     *   <list> x1 x2 x3 x4 </list>
     *   <values> 0 1 2 3 </values>
     *   <occurs> z0 z1 z2 z3 </occurs>
     * </cardinality>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param values the set of values (here int)
     * @param occurs the number of occurences (here variables)
     * @param closed is the constraint is closed
     */
    void buildConstraintCardinality(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> values, std::vector<XCSP3Core::XVariable *> &occurs, bool closed) override;

    //
    /**
     * The callback function related to a cardinality constraint with int values and interval occurs
     * See http://xcsp.org/specifications/cardinality
     *
     * Example:
     * <cardinality>
     *   <list> x1 x2 x3 x4 </list>
     *   <values> 2 5 10 </values>
     *   <occurs> 0..1 1..3 2..3 </occurs>
     * </cardinality>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param values the set of values (here int)
     * @param occurs the number of occurences (here intervals)
     * @param closed is the constraint is closed
     */
    void buildConstraintCardinality(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> values, std::vector<XCSP3Core::XInterval> &occurs, bool closed) override;

    /**
     * The callback function related to a cardinality constraint with variable values and int occurs
     * See http://xcsp.org/specifications/cardinality
     *
     * Example:
     * <cardinality>
     *   <list> x1 x2 x3 x4 </list>
     *   <values> z1 z2 z3 </values>
     *   <occurs> 1 2 3 </occurs>
     * </cardinality>
     *
     * @param id the id (name) of the constraint
     * @param list the list of the constraint (not the scope...)
     * @param values the set of values (here variable)
     * @param occurs the number of occurences (here int)
     * @param closed is the constraint is closed
     */
    void buildConstraintCardinality(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<XCSP3Core::XVariable *> values, std::vector<int> &occurs, bool closed) override;

    /**
     * The callback function related to a cardinality constraint with variable values and variable occurs
     * See http://xcsp.org/specifications/cardinality
     *
     * Example:
     * <cardinality>
     *   <list> x1 x2 x3 x4 </list>
     *   <values> z1 z2 z3 </values>
     *   <occurs> y1 y2 y3 </occurs>
     * </cardinality>
     *
     * @param id the id (name) of the constraint
     * @param list the list of the constraint (not the scope)
     * @param values the set of values (here variables)
     * @param occurs the number of occurences (here variables)
     * @param closed is the constraint is closed
     */
    void buildConstraintCardinality(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<XCSP3Core::XVariable *> values, std::vector<XCSP3Core::XVariable *> &occurs, bool closed) override;

    /**
     * The callback function related to a cardinality constraint with variable values and interval occurs
     * See http://xcsp.org/specifications/cardinality
     *
     * Example:
     * <cardinality>
     *   <list> x1 x2 x3 x4 </list>
     *   <values> z1 z2 z3 </values>
     *   <occurs> 1..2 3..5 2..4 </occurs>
     * </cardinality>
     *
     * @param id the id (name) of the constraint
     * @param list the list of the constraint (not the scope)
     * @param values the set of values (here variables)
     * @param occurs the number of occurences (here intervals)
     * @param closed is the constraint is closed
     */
    void buildConstraintCardinality(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<XCSP3Core::XVariable *> values, std::vector<XCSP3Core::XInterval> &occurs, bool closed) override;
    //--------------------------------------------------------------------------------------
    // Connection constraints
    //--------------------------------------------------------------------------------------

    /**
     * The callback function related to a minimum constraint
     * See http://xcsp.org/specifications/minimum
     *
     * Example:
     * <minimum>
     *    <list> x1 x2 x3 x4 </list>
     *    <condition> (eq,y) </condition>
     * </minimum>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintMinimum(std::string id, std::vector<XCSP3Core::XVariable *> &list, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a minimum constraint
     * See http://xcsp.org/specifications/minimum
     *
     * Example:
     * <minimum>
     *    <list> x1 x2 x3 x4 </list>
     *    <condition> (eq,y) </condition>
     * </minimum>
     *
     * @param id the id (name) of the constraint
     * @param list set of expression
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintMinimum(std::string id, std::vector<XCSP3Core::Tree *> &list, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a maximum constraint
     * See http://xcsp.org/specifications/maximum
     *
     * Example:
     * <maximum>
     *    <list> x1 x2 x3 x4 </list>
     *    <condition> (ge,2) </condition>
     * </maximum>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintMaximum(std::string id, std::vector<XCSP3Core::XVariable *> &list, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a maximum constraint
     * See http://xcsp.org/specifications/maximum
     *
     * Example:
     * <maximum>
     *    <list> add(x1,2) x2 x3 x4 </list>
     *    <condition> (ge,2) </condition>
     * </maximum>
     *
     * @param id the id (name) of the constraint
     * @param list the expressions of the constraint
     * @param xc the condition (see #XCSP3Core::XCondition)
     */
    void buildConstraintMaximum(std::string id, std::vector<XCSP3Core::Tree *> &list, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a element constraint with int value
     * See http://xcsp.org/specifications/element
     *
     * Example:
     * <element>
     *    <list> y[] </list>
     *    <value> 2 </value>
     * </element>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param value the value (here an int)
     */
    void buildConstraintElement(std::string id, std::vector<XCSP3Core::XVariable *> &list, int value) override;

    void buildConstraintElement(std::string id, std::vector<XCSP3Core::XVariable *> &list, XCSP3Core::XVariable *index, int startIndex, XCSP3Core::XCondition &xc) override;
    /**
     * The callback function related to a element constraint matrix
     * See http://xcsp.org/specifications/element
     *
     * Example:  matrix[t][v] = z
     * <element>
     *    <matrix> (x1 x2 x3)(y1 y2 y3) </matrix>
     *    <index> t v </index>
     *    <value> z </value>
     * </element>
     *
     * @param id the id (name) of the constraint
     * @param matrix the matrix (of variables)
     * @param rowIndex the row index
     * @param colIndex the col index
     * @param startRowIndex the start index for rows
     * @param startColIndex the start index for cols
     * @param value the value (here a variable)
     */
    void buildConstraintElement(std::string id, std::vector<std::vector<XCSP3Core::XVariable *>> &matrix, int startRowIndex, XCSP3Core::XVariable *rowIndex, int startColIndex, XCSP3Core::XVariable *colIndex, XCSP3Core::XVariable *value) override;

    /**
     * The callback function related to a element constraint matrix
     * See http://xcsp.org/specifications/element
     *
     * Example:  matrix[t][v] = 2
     * <element>
     *    <matrix> (x1 x2 x3)(y1 y2 y3) </matrix>
     *    <index> t v </index>
     *    <value> z </value>
     * </element>
     *
     * @param id the id (name) of the constraint
     * @param matrix the matrix (of variables)
     * @param rowIndex the row index
     * @param colIndex the col index
     * @param startRowIndex the start index for rows
     * @param startColIndex the start index for cols
     * @param value the value (here an int)
     */
    void buildConstraintElement(std::string id, std::vector<std::vector<XCSP3Core::XVariable *>> &matrix, int startRowIndex, XCSP3Core::XVariable *rowIndex, int startColIndex, XCSP3Core::XVariable *colIndex, int value) override;

    /**
     * The callback function related to a element constraint matrix
     * See http://xcsp.org/specifications/element
     *
     * Example:  matrix[t][v] = z
     * <element>
     *    <matrix> (1 2 3)(4 5 6) </matrix>
     *    <index> t v </index>
     *    <value> z </value>
     * </element>
     *
     * @param id the id (name) of the constraint
     * @param matrix the matrix (here a matrix of int)
     * @param rowIndex the row index
     * @param colIndex the col index
     * @param startRowIndex the start index for rows
     * @param startColIndex the start index for cols
     * @param value the value (here a variable)
     */

    void buildConstraintElement(std::string id, std::vector<std::vector<int>> &matrix, int startRowIndex, XCSP3Core::XVariable *rowIndex, int startColIndex, XCSP3Core::XVariable *colIndex, XCSP3Core::XVariable *value) override;

    /**
     * The callback function related to a element constraint with variable value
     * See http://xcsp.org/specifications/element
     *
     * Example:
     * <element>
     *    <list> y[] </list>
     *    <value> z </value>
     * </element>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param value the value (here a variable)
     */
    void buildConstraintElement(std::string id, std::vector<XCSP3Core::XVariable *> &list, XCSP3Core::XVariable *value) override;

    /**
     * The callback function related to a channel constraint
     * See http://xcsp.org/specifications/channel
     *
     * Example:
     * <channel>
     *    <list> z1 z2 z3 z4 z5 </list>
     * </channel>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     */
    void buildConstraintChannel(std::string id, std::vector<XCSP3Core::XVariable *> &list, int startIndex) override;

    /**
     * The callback function related to a channel constraint
     * See http://xcsp.org/specifications/channel
     *
     * Example:
     * <channel>
     *     <list> x1 x2 x3 x4 </list>
     *     <list> y1 y2 y3 y4 </list>
     * </channel>
     *
     * The size of the array {@code list1} must be less than or equal to the size of {@code list2}.
     *
     * If list1.size() == list2.size() then list1[i] = j <=> list2[j] = i
     * If list1.size() <  list2.size() then list1[i] = j  => list2[j] = i
     *
     * @param id the id (name) of the constraint
     * @param list1 the first list
     * @param startIndex1 the starting index for list1
     * @param list2 the second list
     * @param startIndex2 the starting index for list2
     *
     */
    void buildConstraintChannel(std::string id, std::vector<XCSP3Core::XVariable *> &list1, int startIndex1, std::vector<XCSP3Core::XVariable *> &list2, int startIndex2) override;

    /**
     * The callback function related to a channel constraint with a value
     * See http://xcsp.org/specifications/channel
     *
     * Example:
     * <channel>
     * <list> z1 z2 z3 z4 z5 </list>
     * <value> v </value>
     * </channel>
     *
     * @param id the id (name) of the constraint
     * @param list the list of the constraint not necessary the scope)
     * @param startIndex the starting index for list
     * @param value the vaule
     */
    void buildConstraintChannel(std::string id, std::vector<XCSP3Core::XVariable *> &list, int startIndex, XCSP3Core::XVariable *value) override;

    //--------------------------------------------------------------------------------------
    // packing and schedulling constraints
    //--------------------------------------------------------------------------------------

    /**
     * The callback function related to a no overlap constraint with variable origins and int lenghts
     * See http://xcsp.org/specifications/noOverlap
     *
     * Example:
     * <noOverlap>
     *    <origins> x1 x2 x3 </origins>
     *    <lengths> l1 l2 l3 </lengths>
     * </noOverlap>
     *
     * @param id  the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here int)
     * @param zeroIgnored are zero ignored?
     */
    void buildConstraintNoOverlap(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<int> &lengths, bool zeroIgnored) override;

    /**
     * The callback function related to a no overlap constraint with variable origins and variable lenghts
     * See http://xcsp.org/specifications/noOverlap
     *
     * Example:
     * <noOverlap>
     *    <origins> x1 x2 x3 </origins>
     *    <lengths> z1 z2 z3 </lengths>
     * </noOverlap>
     *
     * @param id  the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here variables)
     * @param zeroIgnored are zero ignored?
     */
    void buildConstraintNoOverlap(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<XCSP3Core::XVariable *> &lengths, bool zeroIgnored) override;

    /**
     * The callback function related to a no overlap constraint with variable origins and 3 dimensional int  lenghts
     * See http://xcsp.org/specifications/noOverlap
     *
     * Example:
     * <noOverlap>
     *    <origins> (x1,y1,z1)(x2,y2,z2)(x3,y3,z3)(x4,y4,z4) </origins>
     *    <lengths> (2,4,1)(4,2,3)(5,1,2)(3,3,2) </lengths>
     * </noOverlap>
     *
     * @param id  the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here std::vector of int)
     * @param zeroIgnored are zero ignored?
     */
    void buildConstraintNoOverlap(std::string id, std::vector<std::vector<XCSP3Core::XVariable *>> &origins, std::vector<std::vector<int>> &lengths, bool zeroIgnored) override;

    /**
     * The callback function related to a no overlap constraint with variable origins and 3 dimensional variable  lenghts
     * See http://xcsp.org/specifications/noOverlap
     *
     * Example:
     * <noOverlap>
     *    <origins> (x1,y1,z1)(x2,y2,z2)(x3,y3,z3)(x4,y4,z4) </origins>
     *    <lengths> (a,b,c)(d,e,f)(g,h,i)(l,m,n) </lengths>
     * </noOverlap>
     *
     * @param id  the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here std::vector of variables)
     * @param zeroIgnored are zero ignored?
     */
    void buildConstraintNoOverlap(std::string id, std::vector<std::vector<XCSP3Core::XVariable *>> &origins, std::vector<std::vector<XCSP3Core::XVariable *>> &lengths, bool zeroIgnored) override;

    /**
     * The callback function related to a cumulative constraint with variable origins, int lengths and int heights
     * See http://xcsp.org/specifications/cumulative
     *
     * Example:
     * <cumulative>
     *     <origins> s1 s2 s3 s4 </origins>
     *     <lengths> 1 2 3 4 </lengths>
     *     <heights> 3 4 5 6 </heights>
     *     <condition> (le,4) </condition>
     * </cumulative>
     *
     * @param id the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here ints)
     * @param heights the std::vector of heights (here ints)
     * @param xc the condition (see XCSP3Core::XCondition)
     */
    void buildConstraintCumulative(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<int> &lengths, std::vector<int> &heights, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a cumulative constraint with variable origin, int lengths and variable heights
     * See http://xcsp.org/specifications/cumulative
     *
     * Example:
     * <cumulative>
     *     <origins> s1 s2 s3 s4 </origins>
     *     <lengths> 1 2 3 4 </lengths>
     *     <heights> h1 h2 h3 h4 </heights>
     *     <condition> (le,4) </condition>
     * </cumulative>
     *
     * @param id the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here ints)
     * @param heights the std::vector of heights (here variables)
     * @param xc the condition (see XCSP3Core::XCondition)
     */
    void buildConstraintCumulative(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<int> &lengths, std::vector<XCSP3Core::XVariable *> &varHeights, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a cumulative constraint with variable origin, variable lengths and int heights
     * See http://xcsp.org/specifications/cumulative
     *
     * Example:
     * <cumulative>
     *     <origins> s1 s2 s3 s4 </origins>
     *     <lengths> l1 l2 l3 l4 </lengths>
     *     <heights> 1 2 3 4 </heights>
     *     <condition> (le,4) </condition>
     * </cumulative>
     *
     * @param id the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here variables)
     * @param heights the std::vector of heights (here ints)
     * @param xc the condition (see XCSP3Core::XCondition)
     */
    void buildConstraintCumulative(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<XCSP3Core::XVariable *> &lengths, std::vector<int> &heights, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a cumulative constraint with variable origin, variable lengths and variable heights
     * See http://xcsp.org/specifications/cumulative
     *
     * Example:
     * <cumulative>
     *     <origins> s1 s2 s3 s4 </origins>
     *     <lengths> l1 l2 l3 l4 </lengths>
     *     <heights> h1 h2 h3 h4 </heights>
     *     <condition> (le,4) </condition>
     * </cumulative>
     *
     * @param id the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here variables)
     * @param heights the std::vector of heights (here variables)
     * @param xc the condition (see XCSP3Core::XCondition)
     */
    void buildConstraintCumulative(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<XCSP3Core::XVariable *> &lengths, std::vector<XCSP3Core::XVariable *> &heights, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a cumulative constraint with variable origin, int lengths and int heights and variable ends
     * See http://xcsp.org/specifications/cumulative
     *
     * Example:
     * <cumulative>
     *     <origins> s1 s2 s3 s4 </origins>
     *     <lengths> 1 2 3 4 </lengths>
     *     <heights> 1 2 3 4 </heights>
     *     <end> e1 e2 e3 e4 </end>
     *     <condition> (le,4) </condition>
     * </cumulative>
     *
     * @param id the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here ints)
     * @param heights the std::vector of heights (here ints)
     * @param ends the std::vector of ends (here variables)
     * @param xc the condition (see XCSP3Core::XCondition)
     */
    void buildConstraintCumulative(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<int> &lengths, std::vector<int> &heights, std::vector<XCSP3Core::XVariable *> &ends, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a cumulative constraint with variable origin, int lengths and variable heights and variable ends
     * See http://xcsp.org/specifications/cumulative
     *
     * Example:
     * <cumulative>
     *     <origins> s1 s2 s3 s4 </origins>
     *     <lengths> 1 2 3 4 </lengths>
     *     <heights> h1 h2 h3 h4 </heights>
     *     <end> e1 e2 e3 e4 </end>
     *     <condition> (le,4) </condition>
     * </cumulative>
     *
     * @param id the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here ints)
     * @param heights the std::vector of heights (here variables)
     * @param ends the std::vector of ends (here variables)
     * @param xc the condition (see XCSP3Core::XCondition)
     */
    void buildConstraintCumulative(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<int> &lengths, std::vector<XCSP3Core::XVariable *> &varHeights, std::vector<XCSP3Core::XVariable *> &ends, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a cumulative constraint with variable origin, variable lengths and int heights and variable ends
     * See http://xcsp.org/specifications/cumulative
     *
     * Example:
     * <cumulative>
     *     <origins> s1 s2 s3 s4 </origins>
     *     <lengths> l1 l2 l3 l4 </lengths>
     *     <heights> 1 2 3 4 </heights>
     *     <end> e1 e2 e3 e4 </end>
     *     <condition> (le,4) </condition>
     * </cumulative>
     *
     * @param id the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here variables)
     * @param heights the std::vector of heights (here ints)
     * @param ends the std::vector of ends (here variables)
     * @param xc the condition (see XCSP3Core::XCondition)
     */
    void buildConstraintCumulative(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<XCSP3Core::XVariable *> &lengths, std::vector<int> &heights, std::vector<XCSP3Core::XVariable *> &ends, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to a cumulative constraint with variable origin, variable lengths and variable heights and variable ends
     * See http://xcsp.org/specifications/cumulative
     *
     * Example:
     * <cumulative>
     *     <origins> s1 s2 s3 s4 </origins>
     *     <lengths> l1 l2 l3 l4 </lengths>
     *     <heights> h1 h2 h3 h4 </heights>
     *     <end> e1 e2 e3 e4 </end>
     *     <condition> (le,4) </condition>
     * </cumulative>
     *
     * @param id the id (name) of the constraint
     * @param origins the std::vector of origins
     * @param lengths the std::vector of lenghts (here variables)
     * @param heights the std::vector of heights (here variables)
     * @param ends the std::vector of ends (here variables)
     * @param xc the condition (see XCSP3Core::XCondition)
     */
    void buildConstraintCumulative(std::string id, std::vector<XCSP3Core::XVariable *> &origins, std::vector<XCSP3Core::XVariable *> &lengths, std::vector<XCSP3Core::XVariable *> &heights,
                                   std::vector<XCSP3Core::XVariable *> &ends, XCSP3Core::XCondition &xc) override;

    /**
     * The callback function related to an instantiation  constraint
     * See http://xcsp.org/specifications/instantiation
     *
     * Example:
     * <instantiation>
     *   <list> x y z </list>
     *   <values> 12 4 30 </values>
     * </instantiation>
     *
     * @param id the id (name) of the constraint
     * @param list the scope of the constraint
     * @param values the value for each variable
     */
    void buildConstraintInstantiation(std::string id, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &values) override;

    //--------------------------------------------------------------------------------------
    // Clause constraints
    //--------------------------------------------------------------------------------------

    /**
     * The callback function related to an clause  constraint
     *
     * Example:
     * <clause>
     *   <list> x not(y) z </list>
     * </clause>
     *
     * @param id the id (name) of the constraint
     * @param positive the positive variables in the clause
     * @param negative the negative variables in the clause
     */
    void buildConstraintClause(std::string id, std::vector<XCSP3Core::XVariable *> &positive, std::vector<XCSP3Core::XVariable *> &negative) override;

    /**
     * The callback function related to an objective minimize a variable
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *    <minimize> x </minimize>
     * </objectives>
     *
     * @param x the variable
     */
    void buildObjectiveMinimizeVariable(XCSP3Core::XVariable *x) override;

    /**
     * The callback function related to an objective maximize a variable
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *    <maximize> x </maximize>
     * </objectives>
     *
     * @param x the variable
     */
    void buildObjectiveMaximizeVariable(XCSP3Core::XVariable *x) override;

    /**
     * The callback function related to an objective minimize a sum/product
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *   <minimize type="sum">
     *     <list> x1 x2 x3 x4 x5 </list>
     *     <coeffs> 2 4 1 4 8 </coeffs>
     *   </minimize>
     * <objectives>
     *
     * @param type SUM, PRODUCT...
     * @param list the scope
     * @param coefs the std::vector of coefficients
     */
    void buildObjectiveMinimize(XCSP3Core::ExpressionObjective type, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &coefs) override;

    /**
     * The callback function related to an objective maximize a sum/product
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *   <maximize type="sum">
     *     <list> x1 x2 x3 x4 x5 </list>
     *     <coeffs> 2 4 1 4 8 </coeffs>
     *   </maximize>
     * <objectives>
     *
     * @param type SUM, PRODUCT...
     * @param list the scope
     * @param coefs the std::vector of coefficients
     */
    void buildObjectiveMaximize(XCSP3Core::ExpressionObjective type, std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &coefs) override;

    /**
     * The callback function related to an objective minimize a sum/product with coefs = 1
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *   <minimize type="sum">
     *     <list> x1 x2 x3 x4 x5 </list>
     *   </minimize>
     * <objectives>
     *
     * @param type SUM, PRODUCT...
     * @param list the scope
     */
    void buildObjectiveMinimize(XCSP3Core::ExpressionObjective type, std::vector<XCSP3Core::XVariable *> &list) override;

    /**
     * The callback function related to an objective maximize a sum/product with coefs = 1
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *   <maximize type="sum">
     *     <list> x1 x2 x3 x4 x5 </list>
     *   </maximize>
     * <objectives>
     *
     * @param type SUM, PRODUCT...
     * @param list the scope
     */
    void buildObjectiveMaximize(XCSP3Core::ExpressionObjective type, std::vector<XCSP3Core::XVariable *> &list) override;

    /**
     * The callback function related to an objective minimize a sum/product
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *   <minimize type="sum">
     *     <list> ne(s[2],2) ne(s[3],3) ... </list>
     *     <coeffs> 2 4 ... </coeffs>
     *   </minimize>
     * <objectives>
     *
     * @param type SUM, PRODUCT...
     * @param trees the expressions
     * @param coefs the std::vector of coefficients
     */
    void buildObjectiveMinimize(XCSP3Core::ExpressionObjective type, std::vector<XCSP3Core::Tree *> &trees, std::vector<int> &coefs) override;

    /**
     * The callback function related to an objective maximize a sum/product
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *   <maximize type="sum">
     *     <list> ne(s[2],2) ne(s[3],3) ... </list>
     *     <coeffs> 2 4 ... </coeffs>
     *   </maximize>
     * <objectives>
     *
     * @param type SUM, PRODUCT...
     * @param list the scope
     * @param coefs the std::vector of coefficients
     */
    void buildObjectiveMaximize(XCSP3Core::ExpressionObjective type, std::vector<XCSP3Core::Tree *> &trees, std::vector<int> &coefs) override;

    /**
     * The callback function related to an objective minimize a sum/product with coefs = 1
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *   <minimize type="sum">
     *     <list> ne(s[2],2) ne(s[3],3) ... </list>
     *   </minimize>
     * <objectives>
     *
     * @param type SUM, PRODUCT...
     * @param list the scope
     */
    void buildObjectiveMinimize(XCSP3Core::ExpressionObjective type, std::vector<XCSP3Core::Tree *> &trees) override;

    /**
     * The callback function related to an objective maximize a sum/product with coefs = 1
     * See http://xcsp.org/specifications/objectives
     *
     * Example:
     * <objectives>
     *   <maximize type="sum">
     *     <list> ne(s[2],2) ne(s[3],3) ... </list>
     *   </maximize>
     * <objectives>
     *
     * @param type SUM, PRODUCT...
     * @param list the scope
     */
    void buildObjectiveMaximize(XCSP3Core::ExpressionObjective type, std::vector<XCSP3Core::Tree *> &trees) override;

    void buildConstraintExtensionAs(string id, vector<XCSP3Core::XVariable *> list, bool support, bool hasStar) override;

private:
    /**
     * Determines the relational operator used in the given condition object.
     *
     * @param cond The condition to get the relational operator of.
     *
     * @return The relation operator used in the condition.
     */
    static Universe::UniverseRelationalOperator operatorOf(XCSP3Core::XCondition &cond);

    static Universe::UniverseRelationalOperator asRelationalOperator(XCSP3Core::OrderType type);

    /**
     * Creates an intension constraint from its tree representation.
     *
     * @param node The node tocreate an intension constraint from.
     *
     * @return The created intension constraint.
     */
    Universe::IUniverseIntensionConstraint *createIntension(XCSP3Core::Node *node);

    /**
     * Converts a std::vector of variables to the std::vector of their names.
     *
     * @param list The list of variables to convert.
     *
     * @return The std::vector of the variable identifiers.
     */
    static std::vector<std::string> toStringVector(const std::vector<XCSP3Core::XVariable *> &list);

    /**
     * Converts a std::vector of variables to the std::vector of their names.
     *
     * @param list The list of variables to convert.
     *
     * @return The std::vector of the variable identifiers.
     */
    static std::vector<std::vector<std::string>> toStringMatrix(const std::vector<std::vector<XCSP3Core::XVariable *>> &list);

    /**
     * Converts a std::vector of integers to a std::vector of big-integers.
     *
     * @param integers The std::vector of integers to convert.
     *
     * @return The std::vector of big integers.
     */
    static std::vector<Universe::BigInteger> toBigIntegerVector(const std::vector<int> &integers);

    /**
     * Converts a std::vector of intension constraint trees to a std::vector of IUniverseIntensionConstraint.
     *
     * @param expressions The std::vector of trees to convert.
     *
     * @return The std::vector of intension constraints.
     */
    std::vector<Universe::IUniverseIntensionConstraint *> toIntensionConstraintVector(
        const std::vector<XCSP3Core::Tree *> &expressions);

    /**
     * Converts a matrix of integers to a matrix of big-integers.
     *
     * @param matrix The matrix of integers to convert.
     *
     * @return The matrix of big integers.
     */
    static std::vector<std::vector<Universe::BigInteger>> toBigIntegerMatrix(
        const std::vector<std::vector<int>> &matrix);
};

}  // namespace Autis

#endif
