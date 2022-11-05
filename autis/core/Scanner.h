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


/**
* @file Scanner.h
* @brief This file represents the header of the Scanner class.
* @author Thibault Falque
* @author Romain Wallon
* @version 0.1.0
* @date 24/10/2022
* @copyright Copyright (c) 2022 Exakis Nelite, Univ Artois & CNRS All rights reserved.
* @license GNU LGPL 3
*/

#ifndef AUTIS_SCANNER_H
#define AUTIS_SCANNER_H

#include <istream>
#include "../../libs/universe/universe/include/core/UniverseType.hpp"

namespace Autis {

    /**
     * @class Scanner
     * @brief The Scanner class allows to read data of various types from an input stream.
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
         * @fn Scanner(std::istream &input)
         * @brief Creates a new Scanner.
         *
         * @param input The input stream to read from.
         */
        explicit Scanner(std::istream &input);

        /**
         * @fn look(char &c)
         * @brief Looks at the next non-blank character in the input stream, but does
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
         * @fn read()
         * @brief Reads the next character from the input stream.
         *
         * @return The read value.
         */
        [[nodiscard]] char read();

        /**
         * @fn read(int& value)
         * @brief Reads the next int value from the input stream.
         * Initial characters that do not form a part of an integer are ignored.
         *
         * @param value The variable in which to store the read value.
         */
        void read(int &value);

        /**
         * @fn read(long long& value)
         * @brief Reads the next long long value from the input stream.
         * Initial characters that do not form a part of an integer are ignored.
         *
         * @param value The variable in which to store the read value.
         */
        void read(long long &value);

        /**
         * @fn skipLine()
         * @brief Skips the next line in the input stream.
         * All characters are ignored until end-of-line is read.
         */
        void skipLine();

        /**
         * @fn eof()
         * @brief Checks whether this scanner has reached end-of-file.
         *
         * @return If EOF has been reached.
         */
        bool eof();

        [[nodiscard]] std::istream &getInput() const;

    };

}

#endif
