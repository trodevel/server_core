/*

Handler interface.

Copyright (C) 2014 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 1404 $ $Date:: 2015-01-16 #$ $Author: serge $

#ifndef I_HANDLER_H
#define I_HANDLER_H

#include "namespace_lib.h"  // NAMESPACE_SERVER_CORE_START

#include <string>               // std::string

NAMESPACE_SERVER_CORE_START

class IHandler
{
public:

    virtual ~IHandler() {}

    virtual const std::string handle( const std::string & s ) = 0;
};

NAMESPACE_SERVER_CORE_END

#endif // I_HANDLER_H
