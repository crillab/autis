#include <memory>

#include "CnfParser.h"
#include "OpbParser.h"
#include "Scanner.h"
#include "parser.h"

#include "../util/except.h"

#include "../problems/writers/ProblemWriter.h"
#include "../problems/writers/DimacsProblemWriter.h"
#include "../problems/writers/OpbProblemWriter.h"

using namespace std;
using namespace rescuer;

void rescuer::parse(const string &path, ParseListener &listener) {
    ifstream input(path);
    parse(input, listener);
}

void rescuer::parse(istream &input, ParseListener &listener) {
    char c;
    Scanner scanner(input);
    unique_ptr<AbstractParser> parser;
    shared_ptr<ProblemWriter> writer;

    if (!scanner.look(c)) {
        // The input stream is empty.
        throw ParseException("Input is empty");
    }

    if ((c == 'c') || (c == 'p')) {
        // The input uses the CNF format.
        parser = make_unique<CnfParser>(scanner, listener);
        writer = make_shared<DimacsProblemWriter>();

    } else if (c == '*') {
        // The input uses the OPB format.
        parser = make_unique<OpbParser>(scanner, listener);
        writer = make_shared<OpbProblemWriter>();

    } else {
        // The format is not recognized.
        throw ParseException("Could not determine input type");
    }

    listener.setWriter(writer);
    parser->parse();
}
