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
 * @file OpbParser.cpp
 * @brief Defines the parser for parsing pseudo-Boolean problems (in the OPB format).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <crillab-except/except.hpp>

#include "crillab-autis/pb/OpbParser.hpp"

using namespace Autis;
using namespace Except;
using namespace std;
using namespace Universe;

OpbParser::OpbParser(Scanner &scanner, IUniversePseudoBooleanSolver *solver) :
        AbstractParser(scanner, solver) {
    // Nothing to do: everything is already initialized.
}

void OpbParser::parse() {
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
        optimization=true;
        throw UnsupportedOperationException("Objective function not supported");

    } else {
        // The "min" keyword was expected but is not present.
        throw ParseException("Keyword `min:' expected");
    }
}

void OpbParser::readConstraint() {
    vector<int> literals;
    vector<BigInteger> coefficients;

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
        vector<int> term;
        BigInteger coefficient;
        readTerm(coefficient, term);
        if (term.size() == 1) {
            // This is a simple term.
            literals.push_back(term[0]);
            coefficients.push_back(coefficient);
            
        } else {
            // This is a product of term.
            throw UnsupportedOperationException("Non linear constraints are not supported");
        }
    }

    // Reading the relational operator.
    string s;
    readRelationalOperator(s);

    // Reading the degree.
    BigInteger degree;
    scanner.readBig(degree);

    // Looking for the semicolon.
    char c;
    if ((!scanner.look(c)) || (c != ';')) {
        throw ParseException("Semi-colon expected at end of constraint");
    }

    // Ending the constraint.
    // We need to consume the ';' character.
    (void) scanner.read();

    // Checking the relational operator to identify the type of the constraint.
    if (s == "=") {
        getConcreteSolver()->addExactly(literals, coefficients, degree);

    } else if (s == ">=") {
        getConcreteSolver()->addAtLeast(literals, coefficients, degree);

    } else {
        getConcreteSolver()->addAtMost(literals, coefficients, degree);
    }
}

void OpbParser::readTerm(BigInteger &coefficient, vector<int> &literals) {
    scanner.readBig(coefficient);
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

IUniversePseudoBooleanSolver *OpbParser::getConcreteSolver() {
    return dynamic_cast<IUniversePseudoBooleanSolver *>(AbstractParser::getConcreteSolver());
}

bool OpbParser::isOptimization() {
    return optimization;
}
