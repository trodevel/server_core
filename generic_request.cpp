/*

Generic Request.

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

// $Revision: 3322 $ $Date:: 2016-01-30 #$ $Author: serge $

#include "generic_request.h"    // self

NAMESPACE_SERVER_CORE_START

GenericRequest::GenericRequest()
{
}


GenericRequest::GenericRequest(
        const ParamMap  & params ):
            params_( params )
{
}

const ParamMap & GenericRequest::get_params() const
{
    return params_;
}

const std::string & GenericRequest::get_param( const std::string & key ) const
{
    static const std::string empty;

    ParamMap::const_iterator it_end = params_.end();
    ParamMap::const_iterator it = params_.find( key );

    if( it == it_end )
        return empty;

    return it->second;
}

bool GenericRequest::has_param( const std::string & key ) const
{
    return params_.count( key ) > 0;
}

bool GenericRequest::has_param( const std::string & key, std::string & value ) const
{
    auto it = params_.find( key );

    if( it == params_.end() )
        return false;

    value = it->second;

    return true;
}

NAMESPACE_SERVER_CORE_END

