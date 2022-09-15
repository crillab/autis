#include "CnfParser.h"

#include "../util/except.h"

using namespace std;
using namespace rescuer;

CnfParser::CnfParser(Scanner &scanner, ParseListener &listener) :
        AbstractParser(scanner, listener) {
    // Nothing to do: all fields are already initialized.
}

void CnfParser::parse() {
    bool inClause = false;
    int nbClausesRead = 0;

    listener.startParse();

    for (char next; scanner.look(next);) {
        if (next == 'c') {
            // This is a comment to skip.
            scanner.skipLine();

        } else if (next == 'p') {
            // This is the problem description line.
            scanner.read(numberOfVariables);
            scanner.read(numberOfConstraints);
            listener.metaData(numberOfVariables, numberOfConstraints);
            scanner.skipLine();

        } else {
            // There is a literal to read.
            int literal = 0;
            scanner.read(literal);

            if (!inClause) {
                // This is a new clause to read.
                listener.beginConstraint();
                inClause = true;
                nbClausesRead++;
            }

            if (literal == 0) {
                // This is the end of a clause.
                listener.constraintRelationalOperator(">=");
                listener.constraintDegree(1);
                listener.endConstraint();
                inClause = false;

            } else {
                // The literal is added if and only if it is correct.
                listener.constraintTerm(1LL, checkLiteral(literal));
            }
        }
    }

    if (inClause) {
        // The last clause has not been added.
        listener.constraintRelationalOperator(">=");
        listener.constraintDegree(1);
        listener.endConstraint();
    }

    if (nbClausesRead != numberOfConstraints) {
        // The number of read clauses is not the expected one.
        throw ParseException("Unexpected number of clauses");
    }

    listener.endParse();
}
