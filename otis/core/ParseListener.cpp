#include "ParseListener.h"

#include "../util/except.h"

using namespace std;
using namespace Otis;

void ParseListener::startParse() {
    // Nothing to do by default.
}

void ParseListener::beginObjective() {
    throw UnsupportedOperationException("Optimization problems are not supported");
}

void ParseListener::objectiveTerm(long long, int) {
    throw UnsupportedOperationException("Optimization problems are not supported");
}

void ParseListener::objectiveProduct(long long, const vector<int> &) {
    throw UnsupportedOperationException("Non-linear constraints are not supported");
}

void ParseListener::endObjective() {
    throw UnsupportedOperationException("Optimization problems are not supported");
}

void ParseListener::constraintProduct(long long, const vector<int> &) {
    throw UnsupportedOperationException("Non-linear constraints are not supported");
}

void ParseListener::endParse() {
    // Nothing to do by default.
}

void ParseListener::setWriter(shared_ptr<ProblemWriter>) {
    // Nothing to do bu default
}
