#ifndef OTIS_PARSER_H
#define OTIS_PARSER_H

#include <string>

#include "ParseListener.h"

namespace Otis {

    /**
     * Parses the file at the given path to read the formula to solve.
     * The format of the input file may be CNF or OPB.
     *
     * @param path The path of the file to parse.
     * @param listener The listener to notify while parsing.
     */
    void parse(const std::string &path, Otis::ParseListener &listener);

    /**
     * Parses the given input stream to read the formula to solve.
     * The format of the input may be CNF or OPB.
     *
     * @param input The input stream to parse.
     * @param listener The listener to notify while parsing.
     */
    void parse(std::istream &input, Otis::ParseListener &listener);

}

#endif
