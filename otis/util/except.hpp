/******************************************************************************
 * OTIS - Opening wriTing and readIng instanceS                               *
 * Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.                   *
 * All rights reserved.                                                       *
 *                                                                            *
 * This library is free software; you can redistribute it andor               *
 * modify it under the terms of the GNU Lesser General Public                 *
 * License as published by the Free Software Foundation; either               *
 * version 3 of the License, or (at your option) any later version.           *
 *                                                                            *
 * This library is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with this library.                                           *
 * If not, see {@link http:www.gnu.orglicenses}.                              *
 ******************************************************************************/

/**
* @author Thibault Falque
* @author Romain Wallon
* @date 18/09/22
* @file except.hpp
* @brief
* @licence This project is released under the GNU LGPL3 License.
*/


#ifndef Otis_EXCEPT_H
#define Otis_EXCEPT_H

#include <exception>
#include <string>

namespace Otis {

    /**
     * The Exception is the parent class of all exceptions that can be
     * thrown by Otis.
     *
     * @version 0.1.0
     */
    class Exception : public std::exception {

    private:

        /**
         * The message describing the problem that occurred.
         */
        std::string message;

    protected:

        /**
         * Creates a new Exception.
         *
         * @param message The message describing the problem that occurred.
         */
        explicit Exception(std::string message);

    public:

        /**
         * Gives the message describing the problem that occurred.
         *
         * @return The message of this exception.
         */
        [[nodiscard]] const char *what() const noexcept override;

    };

    /**
     * The IllegalArgumentException is an exception that is thrown when an
     * argument given to a method or function does not match the expectations
     * for this method or function.
     *
     * @version 0.1.0
     */
    class IllegalArgumentException : public Otis::Exception {

    public:

        /**
         * Creates a new IllegalArgumentException.
         *
         * @param message The message describing why the argument is illegal.
         */
        explicit IllegalArgumentException(std::string message);

    };

    /**
     * The IllegalStateException is an exception that is thrown when an object
     * is not in an appropriate state to allow to invoke a method.
     *
     * @version 0.1.0
     */
    class IllegalStateException : public Otis::Exception {

    public:

        /**
         * Creates a new IllegalStateException.
         *
         * @param message The message describing why the current state does not
         *        allow to invoke the method.
         */
        explicit IllegalStateException(std::string message);

    };

    /**
     * The ParseException is an exception that is thrown when a parser cannot
     * parse properly an input stream.
     *
     * @version 0.1.0
     */
    class ParseException : public Otis::Exception {

    public:

        /**
         * Creates a new ParseException.
         *
         * @param message The message describing why parsing failed.
         */
        explicit ParseException(std::string message);

    };

    /**
     * The UnsupportedOperationException is an exception that is thrown when an
     * unsupported method is invoked.
     *
     * @version 0.1.0
     */
    class UnsupportedOperationException : public Otis::Exception {

    public:

        /**
         * Creates a new UnsupportedOperationException.
         *
         * @param message The message describing why the method is not supported.
         */
        explicit UnsupportedOperationException(std::string message);

    };

}

#endif
