#ifndef RESCUER_SCANNER_H
#define RESCUER_SCANNER_H

#include <istream>

namespace rescuer {

    /**
     * The Scanner class allows to read data of various types from an input stream.
     *
     * @version 0.1.0
     */
    class Scanner {

    private:

        /**
         * The input stream to read from.
         */
        std::istream &input;

    public:

        /**
         * Creates a new Scanner.
         *
         * @param input The input stream to read from.
         */
        explicit Scanner(std::istream &input);

        /**
         * Looks at the next non-blank character in the input stream, but does
         * not consume it.
         *
         * @param c The variable in which to store the read character.
         *
         * @return Whether a non-blank character has been read, meaning that EOF
         *         has not been reached.
         *         If {@code false} is returned, then the content of {@code c}
         *         is undefined.
         */
        [[nodiscard]] bool look(char &c);

        /**
         * Reads the next character from the input stream.
         *
         * @return The read value.
         */
        [[nodiscard]] char read();

        /**
         * Reads the next int value from the input stream.
         * Initial characters that do not form a part of an integer are ignored.
         *
         * @param value The variable in which to store the read value.
         */
        void read(int &value);

        /**
         * Reads the next long long value from the input stream.
         * Initial characters that do not form a part of an integer are ignored.
         *
         * @param value The variable in which to store the read value.
         */
        void read(long long &value);

        /**
         * Skips the next line in the input stream.
         * All characters are ignored until end-of-line is read.
         */
        void skipLine();

        /**
         * Checks whether this scanner has reached end-of-file.
         *
         * @return If EOF has been reached.
         */
        bool eof();

    };

}

#endif
