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

// $Id: service.cpp 679 2014-07-02 16:51:01Z serge $

#include "service.h"                // self

#include <cstring>
#include <iostream>

#include "../tcpserv/server.h"
#include "../utils/dummy_logger.h"  // dummy_log
#include "i_handler.h"              // IHandler

#define MODULENAME      "core::Service"

NAMESPACE_SERVER_CORE_START

Service::Service( tcpserv::Server* server, boost::asio::ip::tcp::socket* socket, IHandler & handler ) :
        tcpserv::Service( server, socket ),
        handler_( handler )
{
}

size_t Service::on_receive( const char* buffer, size_t buffer_size, size_t receive_pos, const boost::system::error_code& error )
{
    dummy_log_trace( MODULENAME, "on_receive: enter" );

    // in case of error close the service and disconnect the client
    if( error )
        close();

    if( receive_pos >= buffer_size )
    {
        dummy_log_trace( MODULENAME, "on_receive: exit" );

        return receive_pos;
    }

    dummy_log_info( MODULENAME, "on_receive: received '%s'", buffer );

    std::string reply = handler_.handle( buffer + receive_pos );

    dummy_log_info( MODULENAME, "on_receive: response '%s'", reply.c_str() );

    send( reply );

    // explicitly close the connection
    close_async();

#ifdef XXX

    // in case of error close the service and disconnect the client
    if( error )
        close();

#endif // XXX

    // update read position
    size_t read_pos = buffer_size;

    dummy_log_trace( MODULENAME, "on_receive: exit" );

    return read_pos;
}

NAMESPACE_SERVER_CORE_END
