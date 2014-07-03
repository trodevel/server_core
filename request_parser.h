/*

Request Parser.

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

// $Id: request_parser.h 680 2014-07-02 16:59:31Z serge $

#include <stdexcept>            // std::runtime_error

#include "generic_request.h"    // GenericRequest

#include "namespace_lib.h"      // NAMESPACE_SERVER_CORE_START

NAMESPACE_SERVER_CORE_START

class RequestParser
{
public:
    struct MalformedRequest: public std::runtime_error
    {
        MalformedRequest( const std::string & str ):
            std::runtime_error( str )
        {}
    };


public:
    static GenericRequest   to_generic_request( const std::string & s );
};

NAMESPACE_SERVER_CORE_END

