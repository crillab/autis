/******************************************************************************
 * AUTIS, a library for parsing combinatorial problems.                       *
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
 * @file AutisNativeXcspCallback.hpp
 * @brief
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 09/11/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef AUTIS_AUTISNATIVEXCSPCALLBACK_H
#define AUTIS_AUTISNATIVEXCSPCALLBACK_H

#include "AutisXcspCallback.hpp"

namespace Autis {
    class AutisNativeXcspCallback : public Autis::AutisXcspCallback {
    public:
        AutisNativeXcspCallback(Universe::IUniverseCspSolver *solver);

        ~AutisNativeXcspCallback() override = default;
    protected:
        Universe::IUniverseIntensionConstraint * createIntension(XCSP3Core::Node *node) override;
    };
}

#endif
