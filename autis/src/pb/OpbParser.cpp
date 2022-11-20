/******************************************************************************
 * AUTIS, a library for parsing combinatorial problems.                       *
 * Copyright (c) 2022 - Exakis Nelite, Univ Artois & CNRS.                    *
 * All rights reserved.                                                       *
 *                                                                            *
 * This library is free software; you can redistribute it andor               *
 * modify it under the terms of the GNU Lesser General Public                 *
 * License as published by the Free Software Foundation; either               *
 * version 3 of the License, or (at your option) any later version.         *
 *                                                                            *
 * This library is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with this library.                                           *
 * If not, see http//:www.gnu.org/licenses.                                   *
 ******************************************************************************/

/**
* @file OpbParser.cpp
* @brief This file represents the definition of the OpbParser class.
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
* @license GNU LGPL 3
*/

#include "../../include/pb/OpbParser.hpp"
#include "../../../libs/exception/except/except.hpp"

using namespace std;
using namespace Autis;

OpbParser::OpbParser(Scanner &scanner, Universe::IUniversePseudoBooleanSolver *solver) :
        AbstractParser(scanner, solver) {
    // Nothing to do: all fields are already initialized.
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
        throw Except::ParseException("Unexpected number of constraints");
    }

}

void OpbParser::readMetaData()  {
    // Checking that the first line is a comment.
    char c = scanner.read();
    if (c != '*') {
        throw Except::ParseException("Metadata line expected");
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
        throw Except::UnsupportedOperationException("Objective function not supported.");
    } else {
        // The "min" keyword was expected but is not present.
        throw Except::ParseException("Keyword `min:' expected");
    }
}

void OpbParser::readConstraint() {

    std::vector<int> literals;
    std::vector<Universe::BigInteger> coefficients;
    for (char c; scanner.look(c);) {
        if ((c == '>') || (c == '=')) {
            // This is the relational operator.
            break;
        }

        if ((c != '-') && (c != '+') && (!isdigit(c))) {
            // A number should have been here.
            throw Except::ParseException("Number expected");
        }

        // Reading the next term of the constraint.
        vector<int> term;
        Universe::BigInteger coefficient;
        readTerm(coefficient, term);
        if (term.size() == 1) {
            // This is a simple term.
            literals.push_back(term[0]);
            coefficients.push_back(coefficient);
        } else {
            // This is a product of term.
            throw Except::UnsupportedOperationException("Non linear constraints are not supported.");
        }
    }

    // Reading the relational operator.
    string s;
    readRelationalOperator(s);

    // Reading the degree.
    Universe::BigInteger degree;
    scanner.read(degree);

    // Looking for the semi-colon.
    char c;
    if ((!scanner.look(c)) || (c != ';')) {
        throw Except::ParseException("Semi-colon expected at end of constraint");
    }

    // Ending the constraint.
    // We need to consume the ';' character.
    (void) scanner.read();
    if(s=="="){
        getConcreteSolver()->addExactly(literals,coefficients,degree);
    }else if(s==">=" ){
        getConcreteSolver()->addAtLeast(literals,coefficients,degree);
    }else{
        getConcreteSolver()->addAtMost(literals,coefficients,degree);
    }
}

void OpbParser::readTerm(Universe::BigInteger &coefficient, vector<int> &literals) {
    scanner.read(coefficient);

    while (readIdentifier(literals));

    if (literals.empty()) {
        throw Except::ParseException("Literal identifier expected");
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
            throw Except::ParseException("Symbol `x' expected");
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
        throw Except::ParseException("Unrecognized relational operator");
    }
}

Universe::IUniversePseudoBooleanSolver *OpbParser::getConcreteSolver() {
    return dynamic_cast<Universe::IUniversePseudoBooleanSolver *>(AbstractParser::getConcreteSolver());
}

