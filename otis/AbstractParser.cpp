#include "AbstractParser.h"

#include "../util/except.h"

#include "../problems/constraints/literals.h"

using namespace std;
using namespace rescuer;

AbstractParser::AbstractParser(Scanner &scanner, ParseListener &listener) :
        scanner(scanner),
        listener(listener),
        numberOfVariables(0),
        numberOfConstraints(0) {
    // Nothing to do: all fields are already initialized.
}

int AbstractParser::checkLiteral(int literal) const {
    int variable = var(literal);
    if ((variable == 0) || (variable > numberOfVariables)) {
        throw ParseException("An invalid literal has been read");
    }
    return literal;
}
