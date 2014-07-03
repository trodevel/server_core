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

// $Id: request_parser.cpp 680 2014-07-02 16:59:31Z serge $

#include "request_parser.h"         // self

#include <sstream>                  // std::ostringstream
#include <boost/lexical_cast.hpp>   // lexical_cast
#include <boost/algorithm/hex.hpp>  // boost::unhex

#include "../utils/tokenizer.h"     // boost wrapper
#include "../utils/trim.h"          // trim

NAMESPACE_SERVER_CORE_START

GenericRequest RequestParser::to_generic_request( const std::string & str )
{
    std::vector< std::string > pars;
    tokenize_to_vector( pars, str, "&" );

    ParamMap    params;

    for( auto & s: pars )
    {
        std::vector< std::string > key_value;
        tokenize_to_vector( key_value, s, "=" );

        if( key_value.size() != 2 )
            continue;

        const std::string & k = trim( key_value[0] );
        const std::string & v = trim( key_value[1] );

        params[ k ] = v;
    }

    GenericRequest res( params );

    return res;

}

NAMESPACE_SERVER_CORE_END
