#include "ParseListener.h"
#include "../../libs/exception/except/except.hpp"


using namespace std;
using namespace Otis;

void ParseListener::startParse() {
    // Nothing to do by default.
}

void ParseListener::beginObjective() {
    throw Except::UnsupportedOperationException("Optimization problems are not supported");
}

void ParseListener::objectiveTerm(long long, int) {
    throw Except::UnsupportedOperationException("Optimization problems are not supported");
}

void ParseListener::objectiveProduct(long long, const vector<int> &) {
    throw Except::UnsupportedOperationException("Non-linear constraints are not supported");
}

void ParseListener::endObjective() {
    throw Except::UnsupportedOperationException("Optimization problems are not supported");
}

void ParseListener::constraintProduct(long long, const vector<int> &) {
    throw Except::UnsupportedOperationException("Non-linear constraints are not supported");
}

void ParseListener::endParse() {
    // Nothing to do by default.
}
