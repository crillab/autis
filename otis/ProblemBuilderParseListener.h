#ifndef RESCUER_PROBLEMBUILDERPARSELISTENER_H
#define RESCUER_PROBLEMBUILDERPARSELISTENER_H

#include <memory>
#include <string>
#include <vector>

#include "ParseListener.h"

#include "../problems/Problem.h"
#include "../problems/constraints/Constraint.h"

namespace rescuer {

    /**
     * The ProblemBuilderParseListener is a listener that allows to build a CNF or a
     * pseudo-Boolean problem that is read from an input stream.
     *
     * @version 0.1.0
     */
    class ProblemBuilderParseListener : public rescuer::ParseListener {

    private:

        /**
         * The number of variables of the read problem.
         */
        int numberOfVariables;

        /**
         * The constraints of the read problem.
         */
        std::vector<std::shared_ptr<rescuer::Constraint>> constraints;

        /**
         * The literals of the current constraint.
         */
        std::vector<int> literals;

        /**
         * The coefficients of the current constraint.
         */
        std::vector<long long> coefficients;

        /**
         * The relational operator of the current constraint.
         */
        std::string relationalOperator;

        /**
         * The degree of the current constraint.
         */
        long long degree;

        /**
         * Whether all the coefficients of the current constraint are equal to 1.
         */
        bool allCoefficientsAre1;

        /**
         * The problem writer to use for the problem.
         */
        std::shared_ptr<rescuer::ProblemWriter> problemWriter;

    public:

        /**
         * Creates a new ProblemBuilderParseListener.
         */
        explicit ProblemBuilderParseListener();

        /**
         * Sets the writer for the problem that will be parsed.
         *
         * @param writer The writer for the problem.
         */
        void setWriter(std::shared_ptr<rescuer::ProblemWriter> writer) override;

        /**
         * Initializes the internal data structures of this listener to handle
         * the given number of variables and the given number of constraints.
         *
         * @param nbVariables The number of variables.
         * @param nbConstraints The number of constraints.
         */
        void metaData(int nbVariables, int nbConstraints) override;

        /**
         * Sets up the internal data structures to prepare the reading of a new
         * constraint.
         */
        void beginConstraint() override;

        /**
         * Adds a term to the constraint that is being built.
         *
         * @param coefficient The coefficient of the term.
         * @param literal The literal of the term.
         */
        void constraintTerm(long long coefficient, int literal) override;

        /**
         * Sets the relational operator of the constraint that is being built.
         *
         * @param relationalOperator The relational operator, which is one of
         *        "<", "<=", "=", ">=", ">".
         */
        void constraintRelationalOperator(std::string relationalOperator) override;

        /**
         * Sets the degree of the constraint that is being built.
         *
         * @param degree The degree of the constraint.
         */
        void constraintDegree(long long degree) override;

        /**
         * Instantiates the constraint that is currently being built.
         */
        void endConstraint() override;

        /**
         * Builds the problem that has been read.
         *
         * @return The read problem.
         */
        [[nodiscard]] std::shared_ptr<rescuer::Problem> buildProblem();

    };

}

#endif
