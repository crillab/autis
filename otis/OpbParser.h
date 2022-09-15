#ifndef RESCUER_OPBPARSER_H
#define RESCUER_OPBPARSER_H

#include <fstream>
#include <string>
#include <vector>

#include "AbstractParser.h"

namespace rescuer {

    /**
     * The OpbParser specializes AbstractParser to read inputs written
     * using the OPB format.
     *
     * @version 0.1.0
     */
    class OpbParser : public rescuer::AbstractParser {

    public:

        /**
         * Creates a new OpbParser which uses the given scanner and notifies
         * the given listener.
         *
         * @param scanner The scanner used to read the input stream.
         * @param listener The listener to notify.
         */
        OpbParser(rescuer::Scanner &scanner, rescuer::ParseListener &listener);

        /**
         * Parses the input to read the problem to solve.
         */
        void parse() override;

    private:

        /**
         * Reads the first comment line to get the number of variables and
         * the number of constraints in the input.
         */
        void readMetaData();

        /**
         * Skips comments from the input.
         */
        void skipComments();

        /**
         * Reads the objective line (if any).
         */
        void readObjective();

        /**
         * Reads a constraint.
         */
        void readConstraint();

        /**
         * Reads a term (either from the objective function or from a constraint)
         * and stores it into coefficient and literals.
         *
         * @param coefficient The coefficient of the term.
         * @param literals The literals of the term (if there is more than one,
         *        this is a product of literals).
         */
        void readTerm(long long &coefficient, std::vector<int> &literals);

        /**
         * Reads an identifier from the stream and appends it to literals.
         *
         * @param literals The current list of read identifiers.
         *
         * @return Whether an identifier was read.
         */
        bool readIdentifier(std::vector<int> &literals);

        /**
         * Reads a relational operator from the input stream and stores it into
         * relationalOperator.
         *
         * @param relationalOperator The reference in which to hold the relational
         *        operator that has been read.
         */
        void readRelationalOperator(std::string &relationalOperator);

    };

}

#endif
