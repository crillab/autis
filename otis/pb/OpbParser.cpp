#include "OpbParser.h"

#include "../util/except.h"

using namespace std;
using namespace Otis;

OpbParser::OpbParser(Scanner &scanner, ParseListener &listener) :
        AbstractParser(scanner, listener) {
    // Nothing to do: all fields are already initialized.
}

void OpbParser::parse() {
    listener.startParse();

    // Reading the header of the file.
    readMetaData();
    skipComments();

    // Reading the objective function.
    readObjective();

    // Reading the constraints.
    int nbConstraintsRead = 0;
    for (char c; scanner.look(c);) {
        if (c == '*') {
            // The rest of the line is a comment.
            skipComments();
        }

        // Reading the next constraint.
        readConstraint();
        nbConstraintsRead++;
    }

    if (nbConstraintsRead != numberOfConstraints) {
        // The number of read constraints is not the expected one.
        throw ParseException("Unexpected number of constraints");
    }

    listener.endParse();
}

void OpbParser::readMetaData()  {
    // Checking that the first line is a comment.
    char c = scanner.read();
    if (c != '*') {
        throw ParseException("Metadata line expected");
    }

    // Reading the metadata of the input.
    scanner.read(numberOfVariables);
    scanner.read(numberOfConstraints);

    // Ignoring the rest of the line.
    scanner.skipLine();

    // Notifying the listener.
    listener.metaData(numberOfVariables, numberOfConstraints);
}

void OpbParser::skipComments() {
    for (char c; scanner.look(c) && (c == '*');) {
        scanner.skipLine();
    }
}

void OpbParser::readObjective() {
    // Reading the objective line (if any).
    char c;
    if ((!scanner.look(c)) || (c != 'm')) {
        // There is no objective function.
        return;
    }

    // Reading the objective function.
    if ((scanner.read() == 'm') && (scanner.read() == 'i') && (scanner.read() == 'n') && (scanner.read() == ':')) {
        listener.beginObjective();

        while (scanner.look(c)) {
            if (c == ';') {
                // This is the end of the objective function.
                // We need to consume the ';' character.
                (void) scanner.read();
                break;
            }

            if ((c != '-') && (c != '+') && (!isdigit(c))) {
                // A number should have been here.
                throw ParseException("Number expected");
            }

            // Reading the next term of the objective function.
            long long coefficient;
            vector<int> literals;
            readTerm(coefficient, literals);
            if (literals.size() == 1) {
                // This is a simple term.
                listener.objectiveTerm(coefficient, literals[0]);

            } else {
                // This is a product of literals.
                listener.objectiveProduct(coefficient, literals);
            }
        }

        listener.endObjective();

    } else {
        // The "min" keyword was expected but is not present.
        throw ParseException("Keyword `min:' expected");
    }
}

void OpbParser::readConstraint() {
    listener.beginConstraint();

    for (char c; scanner.look(c);) {
        if ((c == '>') || (c == '=')) {
            // This is the relational operator.
            break;
        }

        if ((c != '-') && (c != '+') && (!isdigit(c))) {
            // A number should have been here.
            throw ParseException("Number expected");
        }

        // Reading the next term of the constraint.
        vector<int> literals;
        long long coefficient;
        readTerm(coefficient, literals);
        if (literals.size() == 1) {
            // This is a simple term.
            listener.constraintTerm(coefficient, literals[0]);

        } else {
            // This is a product of literals.
            listener.constraintProduct(coefficient, literals);
        }
    }

    // Reading the relational operator.
    string s;
    readRelationalOperator(s);
    listener.constraintRelationalOperator(s);

    // Reading the degree.
    long long degree;
    scanner.read(degree);
    listener.constraintDegree(degree);

    // Looking for the semi-colon.
    char c;
    if ((!scanner.look(c)) || (c != ';')) {
        throw ParseException("Semi-colon expected at end of constraint");
    }

    // Ending the constraint.
    // We need to consume the ';' character.
    (void) scanner.read();
    listener.endConstraint();
}

void OpbParser::readTerm(long long &coefficient, vector<int> &literals) {
    scanner.read(coefficient);

    while (readIdentifier(literals));

    if (literals.empty()) {
        throw ParseException("Literal identifier expected");
    }
}

bool OpbParser::readIdentifier(vector<int> &literals) {
    bool negated = false;

    // Reading the first character.
    char c;
    if (!scanner.look(c)) {
        return false;
    }

    // Checking whether the literal is negated.
    if (c == '~') {
        // Consuming the negation.
        (void) scanner.read();
        negated = true;

        // Reading the 'x' symbol.
        if ((scanner.look(c)) || (c != 'x')) {
            throw ParseException("Symbol `x' expected");
        }
    }

    if (c == 'x') {
        // Reading the literal identifier.
        int literal;
        scanner.read(literal);

        // Adding the literal to the list.
        literals.push_back(negated ? -checkLiteral(literal) : checkLiteral(literal));
        return true;
    }

    return false;
}

void OpbParser::readRelationalOperator(string &relationalOperator) {
    // Looking at the first character.
    char c1 = scanner.read();

    if (c1 == '=') {
        relationalOperator = "=";
        return;
    }

    // Looking at the second character.
    char c2 = scanner.read();

    if ((c1 == '>') && (c2 == '=')) {
        relationalOperator = ">=";

    } else if ((c1 == '<') && (c2 == '=')) {
        relationalOperator = "<=";

    } else {
        throw ParseException("Unrecognized relational operator");
    }
}
