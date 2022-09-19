#include "ProblemBuilderParseListener.h"

#include "../problems/constraints/RelationalOperator.h"

using namespace std;
using namespace Otis;

ProblemBuilderParseListener::ProblemBuilderParseListener() :
        numberOfVariables(),
        constraints(),
        literals(),
        coefficients(),
        relationalOperator(),
        degree(),
        allCoefficientsAre1(true) {
    // Nothing to do: all fields are already initialized.
}

void ProblemBuilderParseListener::metaData(int nbVariables, int nbConstraints) {
    numberOfVariables = nbVariables;
    constraints.reserve(nbConstraints);
}

void ProblemBuilderParseListener::beginConstraint() {
    literals.clear();
    coefficients.clear();
    relationalOperator = "";
    degree = 0;
    allCoefficientsAre1 = true;
}

void ProblemBuilderParseListener::constraintTerm(long long coefficient, int literal) {
    coefficients.push_back(coefficient);
    literals.push_back(literal);

    if (coefficient != 1) {
        allCoefficientsAre1 = false;
    }
}

void ProblemBuilderParseListener::constraintRelationalOperator(string relOp) {
    relationalOperator = relOp;
}

void ProblemBuilderParseListener::constraintDegree(long long deg) {
    degree = deg;
}

void ProblemBuilderParseListener::endConstraint() {
    if (allCoefficientsAre1 && (relationalOperator == ">=") && (degree == 1)) {
        // The constraint is a clause.
        constraints.push_back(make_shared<Clause>(literals));
        return;
    }

    auto &relOp = RelationalOperator::valueOf(relationalOperator);
    if (allCoefficientsAre1) {
        // The constraint is a general cardinality constraint.
        constraints.push_back(make_shared<CardinalityConstraint>(literals, relOp, degree));
        return;
    }

    // The constraint is a general pseudo-Boolean constraint.
    constraints.push_back(make_shared<PseudoBooleanConstraint>(literals, coefficients, relOp, degree));
}

shared_ptr<Problem> ProblemBuilderParseListener::buildProblem() {
    auto problem = make_shared<Problem>(numberOfVariables, constraints);
    problem->setWriter(problemWriter);
    return problem;
}

void ProblemBuilderParseListener::setWriter(shared_ptr<ProblemWriter> writer) {
    this->problemWriter = move(writer);
}
