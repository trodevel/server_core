/*

Boost based service.

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

// $Id: service.h 679 2014-07-02 16:51:01Z serge $

#include "../tcpserv/service.h"

#include "namespace_lib.h"      // NAMESPACE_SERVER_CORE_START

NAMESPACE_SERVER_CORE_START

class IHandler;

class Service: public tcpserv::Service
{
    typedef tcpserv::Service Base;

public:

    Service( tcpserv::Server* server, boost::asio::ip::tcp::socket* socket, IHandler & handler );

protected:

    virtual size_t on_receive( const char* buffer, size_t buffer_size, size_t receive_pos, const boost::system::error_code& error );

private:
    IHandler    & handler_;

};

NAMESPACE_SERVER_CORE_END
