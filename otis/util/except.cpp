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

#include "except.hpp"

using namespace std;
using namespace Otis;

Exception::Exception(string message) :
        message(move(message)) {
    // Nothing to do: all fields are already initialized.
}

const char *Exception::what() const noexcept {
    return message.c_str();
}

IllegalArgumentException::IllegalArgumentException(string message) :
        Exception(move(message)) {
    // Nothing to do: all fields are already initialized.
}

IllegalStateException::IllegalStateException(string message) :
        Exception(move(message)) {
    // Nothing to do: all fields are already initialized.
}

ParseException::ParseException(string message) :
        Exception(move(message)) {
    // Nothing to do: all fields are already initialized.
}

UnsupportedOperationException::UnsupportedOperationException(string message) :
        Exception(move(message)) {
    // Nothing to do: all fields are already initialized.
}
