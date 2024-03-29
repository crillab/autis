/******************************************************************************
 * AUTIS, A Unified Tool for parsIng problemS                                 *
 * Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.                   *
 * All rights reserved.                                                       *
 *                                                                            *
 * This library is free software; you can redistribute it and/or modify it    *
 * under the terms of the GNU Lesser General Public License as published by   *
 * the Free Software Foundation; either version 3 of the License, or (at your *
 * option) any later version.                                                 *
 *                                                                            *
 * This library is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.                                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with this library.                                           *
 * If not, see http://www.gnu.org/licenses.                                   *
 ******************************************************************************/

/**
 * @file Scanner.hpp
 * @brief Allows to read data of various types from an input stream.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 24/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef AUTIS_SCANNER_HPP
#define AUTIS_SCANNER_HPP

#include <istream>

#include <crillab-universe/core/UniverseType.hpp>

namespace Autis {

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
         * Gives the input stream from which this scanner reads.
         *
         * @return The input stream.
         */
        [[nodiscard]] std::istream &getInput() const;

        /**
         * Looks at the next non-blank character in the input stream, but does
         * not consume it.
         *
         * @param c The variable in which to store the read character.
         *
         * @return Whether a non-blank character has been read, meaning that EOF
         *         has not been reached.
         *         If false is returned, then the content of c is undefined.
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
         * Reads the next big integer value from the input stream.
         * Initial characters that do not form a part of an integer are ignored.
         *
         * @param value The variable in which to store the read value.
         */
        void readBig(Universe::BigInteger &value);

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
