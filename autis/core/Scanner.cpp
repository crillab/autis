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

#include <cctype>
#include <limits>

#include "Scanner.h"
#include "../../libs/exception/except/except.hpp"


using namespace std;
using namespace Autis;

Scanner::Scanner(istream &input) :
        input(input) {
    // Nothing to do: all fields are already initialized.
}

bool Scanner::look(char &c) {
    do {
        // Reading the next character.
        c = read();
    } while (!eof() && isspace(c));

    if (eof()) {
        // There is no more character to read.
        return false;
    }

    // Putting back the read character, which will be consumed later on.
    input.putback(c);
    return true;
}

char Scanner::read() {
    return (char) input.get();
}

void Scanner::read(int &value) {
    long long longValue = 0LL;
    read(longValue);
    value = (int) longValue;
}

void Scanner::read(Universe::BigInteger &value) {
    char c;
    int sign = 1;

    // Moving to the next eligible character.
    do {
        c = read();
    } while ((!eof()) && (!isdigit(c)) && (c != '+') && (c != '-'));

    // Considering the sign of the number.
    if (c == '-') {
        // The number is negative.
        sign = -1;
        c = read();

    } else if (c == '+') {
        // This sign is simply ignored.
        c = read();
    }

    // Making sure that at least one digit is present in the number.
    if (eof() || !isdigit(c)) {
        throw Except::ParseException("Non-digit character found while looking for a number");
    }

    // Computing the value of the number.
    for (value = 0; (!eof()) && (isdigit(c)); c = read()) {
        value = 10 * value + (c - '0');
    }
    value *= sign;

    if (!eof()) {
        // The last (non-digit) character is put back.
        input.putback(c);
    }
}

void Scanner::skipLine() {
    input.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool Scanner::eof() {
    return input.eof();
}

istream &Scanner::getInput() const {
    return input;
}
