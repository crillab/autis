#ifndef OTIS_ABSTRACTPARSER_H
#define OTIS_ABSTRACTPARSER_H

#include <istream>
#include <memory>

#include "ParseListener.h"
#include "Scanner.h"

namespace Otis {

    /**
     * The AbstractParser is the parent class of classes used to parse
     * input streams so as to read a problem to solve.
     *
     * @version 0.1.0
     */
    class AbstractParser {

    protected:

        /**
         * The scanner used to read the input stream.
         */
        Otis::Scanner &scanner;

        /**
         * The listener to notify while parsing.
         */
        Otis::ParseListener &listener;

        /**
         * The number of variables in the problem that is being read.
         */
        int numberOfVariables;

        /**
         * The number of constraints in the problem that is being read.
         */
        int numberOfConstraints;

        /**
         * Creates a new parser which uses the given scanner and notifies
         * the given listener.
         *
         * @param scanner The scanner used to read the input stream.
         * @param listener The listener to notify.
         */
        explicit AbstractParser(Otis::Scanner &scanner,
                                Otis::ParseListener &listener);

        /**
         * Checks whether the given literal is correct w.r.t. the expected
         * number of variables.
         *
         * @param literal The literal to check.
         *
         * @return The given literal.
         */
        [[nodiscard]] int checkLiteral(int literal) const;

    public:

        /**
         * Parses the input to read the problem to solve.
         */
        virtual void parse() = 0;

    };

}

#endif
