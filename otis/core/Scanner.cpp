#include <cctype>
#include <limits>

#include "Scanner.h"

#include "../util/except.h"

using namespace std;
using namespace Otis;

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

void Scanner::read(long long &value) {
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
        throw ParseException("Non-digit character found while looking for a number");
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
