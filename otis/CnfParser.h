#ifndef RESCUER_CNFPARSER_H
#define RESCUER_CNFPARSER_H

#include "AbstractParser.h"

namespace rescuer {

    /**
     * The CnfParser specializes AbstractParser to read inputs written
     * using the CNF format.
     *
     * @version 0.1.0
     */
    class CnfParser : public rescuer::AbstractParser {

    public:

        /**
         * Creates a new CnfParser which uses the given scanner and notifies
         * the given listener.
         *
         * @param scanner The scanner used to read the input stream.
         * @param listener The listener to notify.
         */
        explicit CnfParser(rescuer::Scanner &scanner, rescuer::ParseListener &listener);

        /**
         * Parses the input to read the problem to solve.
         */
        void parse() override;

    };

}

#endif
