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

#ifndef GENERIC_REQUEST_H
#define GENERIC_REQUEST_H

#include "namespace_lib.h"      // NAMESPACE_SERVER_CORE_START

#include "param_map.h"  // ParamMap

NAMESPACE_SERVER_CORE_START

class GenericRequest
{
    friend class StrHelper;

public:
    GenericRequest();

    GenericRequest(
            const ParamMap  & params );

    const ParamMap  & get_params() const;

    const std::string & get_param( const std::string & key ) const;
    bool has_param( const std::string & key ) const;
    bool has_param( const std::string & key, std::string & value ) const;

private:
    ParamMap        params_;
};

NAMESPACE_SERVER_CORE_END

#endif // GENERIC_REQUEST_H
