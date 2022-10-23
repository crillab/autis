#include "CnfParser.h"

#include "../../libs/exception/except/except.hpp"

using namespace std;
using namespace Otis;

CnfParser::CnfParser(Scanner &scanner, Universe::IUniverseSatSolver *solver) :
        AbstractParser(scanner, solver) {
    // Nothing to do: all fields are already initialized.
}

void CnfParser::parse() {
    bool inClause = false;
    int nbClausesRead = 0;

    std::vector<int> clause;

    for (char next; scanner.look(next);) {
        if (next == 'c') {
            // This is a comment to skip.
            scanner.skipLine();

        } else if (next == 'p') {
            // This is the problem description line.
            scanner.read(numberOfVariables);
            scanner.read(numberOfConstraints);
            scanner.skipLine();

        } else {
            // There is a literal to read.
            int literal = 0;
            scanner.read(literal);

            if (!inClause) {
                // This is a new clause to read.
                clause.clear();
                inClause = true;
                nbClausesRead++;
            }

            if (literal == 0) {
                // This is the end of a clause.
                getConcreteSolver()->addClause(clause);
                inClause = false;

            } else {
                // The literal is added if and only if it is correct.
                clause.push_back(checkLiteral(literal));
            }
        }
    }

    if (inClause) {
        // The last clause has not been added.
        getConcreteSolver()->addClause(clause);
    }

    if (nbClausesRead != numberOfConstraints) {
        // The number of read clauses is not the expected one.
        throw Except::ParseException("Unexpected number of clauses");
    }
}

Universe::IUniverseSatSolver *CnfParser::getConcreteSolver() {
    return dynamic_cast<Universe::IUniverseSatSolver *>(AbstractParser::getConcreteSolver());
}


