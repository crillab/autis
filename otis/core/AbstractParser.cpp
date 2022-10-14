#include "AbstractParser.h"
#include "../../libs/exception/except/except.hpp"


using namespace std;
using namespace Otis;

AbstractParser::AbstractParser(Scanner &scanner, Universe::IUniverseSolver* solver) :
        scanner(scanner),
        solver(solver),
        numberOfVariables(0),
        numberOfConstraints(0) {
    // Nothing to do: all fields are already initialized.
}

int AbstractParser::checkLiteral(int literal) const {
    int variable = abs(literal);
    if ((variable == 0) || (variable > numberOfVariables)) {
        throw Except::ParseException("An invalid literal has been read");
    }
    return literal;
}

Universe::IUniverseSolver *AbstractParser::getConcreteSolver() {
    return solver;
}
