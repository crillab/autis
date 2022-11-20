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

#include "XCSP3CoreCallbacks.h"

#include "../../../libs/universe/universe/include/csp/IUniverseCspSolver.hpp"
#include "../../../libs/universe/universe/include/csp/intension/AbstractUniverseIntensionConstraintFactory.hpp"

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
         * nNtifies this callback that a new variable has been encountered.
         *
         * @param id The identifier of the variable.
         * @param minValue The minimum value of the domain of the variable.
         * @param maxValue The maximum value of the domain of the variable.
         */
        void buildVariableInteger(std::string id, int minValue, int maxValue) override;

        /**
         * Notifies this callback that a new variable has been encountered.
         *
         * @param id The identifier of the variable.
         * @param values The values of the domain of the variable.
         */
        void buildVariableInteger(std::string id, std::vector<int> &values) override;

        /**
         * Notifies this callback that a new all-different constraint has been encountered.
         *
         * @param id The identifier of the constraint.
         * @param list The variables appearing in the constraint.
         */
        void buildConstraintAlldifferent(std::string id, std::vector<XCSP3Core::XVariable *> &list) override;

        /**
         * Notifies this callback that a new intension constraint has been encountered.
         *
         * @param id The identifier of the constraint.
         * @param tree The tree representation of the intension constraint.
         */
        void buildConstraintIntension(std::string id, XCSP3Core::Tree *tree) override;

        /**
         * Notifies this callback that a new extension constraint has been encountered.
         *
         * @param id The identifier of the constraint.
         * @param variable The variable appearing in the constraint.
         * @param tuples The allowed/forbidden values.
         * @param support Whether the constraint is a support (i.e., values are allowed one).
         * @param hasStar Whether the value contain stars.
         */
        void buildConstraintExtension(std::string id, XCSP3Core::XVariable *variable,
                 std::vector<int> &tuples, bool support, bool hasStar) override;

        /**
         * Notifies this callback that a new extension constraint has been encountered.
         *
         * @param id The identifier of the constraint.
         * @param list The variables appearing in the constraint.
         * @param tuples The tuples of the allowed/forbidden values.
         * @param support Whether the constraint is a support (i.e., tuples are allowed one).
         * @param hasStar Whether the tuples contain stars.
         */
        void buildConstraintExtension(std::string id, std::vector<XCSP3Core::XVariable *> list,
                 std::vector<std::vector<int>> &tuples, bool support, bool hasStar) override;

        /**
         * Notifies this callback that a new sum constraint has been encountered.
         *
         * @param id The identifier of the constraint.
         * @param list The variables appearing in the constraint.
         * @param cond The condition on the sum.
         */
        void buildConstraintSum(std::string id, std::vector<XCSP3Core::XVariable *> &list,
                 XCSP3Core::XCondition &cond) override;

        /**
         * Notifies this callback that a new sum constraint has been encountered.
         *
         * @param id The identifier of the constraint.
         * @param list The variables appearing in the constraint.
         * @param coeffs The coefficients of the variables.
         * @param cond The condition on the sum.
         */
        void buildConstraintSum(std::string id, std::vector<XCSP3Core::XVariable *> &list,
                 std::vector<int> &coeffs, XCSP3Core::XCondition &cond) override;

        /**
         * Notifies this callback that a new sum constraint has been encountered.
         *
         * @param id The identifier of the constraint.
         * @param list The variables appearing in the constraint.
         * @param coeffs The variables corresponding to the coefficients of the variables.
         * @param cond The condition on the sum.
         */
        void buildConstraintSum(std::string id, std::vector<XCSP3Core::XVariable *> &list,
                 std::vector<XCSP3Core::XVariable *> &coeffs, XCSP3Core::XCondition &cond) override;

        /**
         * Notifies this callback that a new sum constraint has been encountered.
         *
         * @param id The identifier of the constraint.
         * @param trees The expressions appearing in the constraint.
         * @param cond The condition on the sum.
         */
        void buildConstraintSum(std::string id, std::vector<XCSP3Core::Tree *> &trees,
                 XCSP3Core::XCondition &cond) override;

        /**
         * Notifies this callback that a new sum constraint has been encountered.
         *
         * @param id The identifier of the constraint.
         * @param trees The expressions appearing in the constraint.
         * @param coeffs The the coefficients of the expression.
         * @param cond The condition on the sum.
         */
        void buildConstraintSum(std::string id, std::vector<XCSP3Core::Tree *> &trees,
                 std::vector<int> &coefs, XCSP3Core::XCondition &cond) override;

        /**
         * Adds an objective function to maximize.
         *
         * @param type The type of the objective function.
         * @param list The variables appearing in the objective function.
         * @param coefs The coefficients of the variables.
         */
        void buildObjectiveMaximize(XCSP3Core::ExpressionObjective type,
                 std::vector<XCSP3Core::XVariable *> &list, std::vector<int> &coefs) override;

    private:

        /**
         * Determines the relational operator used in the given condition object.
         *
         * @param cond The condition to get the relational operator of.
         *
         * @return The relation operator used in the condition.
         */
        static Universe::UniverseRelationalOperator operatorOf(XCSP3Core::XCondition &cond);

        /**
         * Creates an intension constraint from its tree representation.
         *
         * @param node The node tocreate an intension constraint from.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *createIntension(XCSP3Core::Node *node);

        /**
         * Converts a vector of variables to the vector of their names.
         *
         * @param list The list of variables to convert.
         *
         * @return The vector of the variable identifiers.
         */
        static std::vector<string> toStringVector(const std::vector<XCSP3Core::XVariable *> &list);

        /**
         * Converts a vector of integers to a vector of big-integers.
         *
         * @param integers The vector of integers to convert.
         *
         * @return The vector of big integers.
         */
        static std::vector<Universe::BigInteger> toBigIntegerVector(const std::vector<int> &integers);

        /**
         * Converts a vector of intension constraint trees to a vector of IUniverseIntensionConstraint.
         *
         * @param expressions The vector of trees to convert.
         *
         * @return The vector of intension constraints.
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

}

#endif
