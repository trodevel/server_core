/*

Key-Value map - Parameter Map.

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

#ifndef CORE_PARAM_MAP_H
#define CORE_PARAM_MAP_H

#include "namespace_lib.h"      // NAMESPACE_SERVER_CORE_START

#include <string>       // std::string
#include <map>

NAMESPACE_SERVER_CORE_START

typedef std::map< std::string, std::string >    ParamMap;
typedef ParamMap::key_type                      Param;

NAMESPACE_SERVER_CORE_END

#endif // CORE_PARAM_MAP_H
