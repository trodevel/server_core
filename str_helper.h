/*

String Helper. Provides to_string() function.

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

// $Id: str_helper.h 681 2014-07-02 17:04:54Z serge $

#include <string>

#include "generic_request.h"    // GenericRequest

#include "namespace_lib.h"      // NAMESPACE_SERVER_CORE_START

NAMESPACE_SERVER_CORE_START

class GenericRequest;

class StrHelper
{
public:
    static std::string to_string( const GenericRequest & l );

private:
    static std::string to_string( const ParamMap & l );
    static std::string to_string( const ParamMap::value_type & l );
};

NAMESPACE_SERVER_CORE_END
