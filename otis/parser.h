#ifndef RESCUER_PARSER_H
#define RESCUER_PARSER_H

#include <string>

#include "ParseListener.h"

namespace rescuer {

    /**
     * Parses the file at the given path to read the formula to solve.
     * The format of the input file may be CNF or OPB.
     *
     * @param path The path of the file to parse.
     * @param listener The listener to notify while parsing.
     */
    void parse(const std::string &path, rescuer::ParseListener &listener);

    /**
     * Parses the given input stream to read the formula to solve.
     * The format of the input may be CNF or OPB.
     *
     * @param input The input stream to parse.
     * @param listener The listener to notify while parsing.
     */
    void parse(std::istream &input, rescuer::ParseListener &listener);

}

#endif
