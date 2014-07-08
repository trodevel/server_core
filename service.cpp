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

// $Id: service.cpp 712 2014-07-07 17:01:00Z serge $

#include "service.h"                // self

#include <cstring>
#include <iostream>

#include "../tcpserv/server.h"
#include "../utils/dummy_logger.h"  // dummy_log
#include "i_handler.h"              // IHandler

#define MODULENAME      "server_core::Service"

NAMESPACE_SERVER_CORE_START

const int RECV_BUFFER_SIZE  = 32768;

Service::Service( tcpserv::Server* server, boost::asio::ip::tcp::socket* socket, IHandler & handler ) :
        tcpserv::Service( server, socket ),
        handler_( handler )
{
    recv_buffer_.reserve( RECV_BUFFER_SIZE );
}

size_t Service::on_receive( const char* buffer, size_t buffer_size, size_t receive_pos, const boost::system::error_code& error )
{
    static const std::string eom( "<EOM>" );    // End-Of-Message token

    dummy_log_trace( MODULENAME, "on_receive: enter" );

    // in case of error close the service and disconnect the client
    if( error )
        close();

    if( receive_pos >= buffer_size )
    {
        dummy_log_trace( MODULENAME, "on_receive: exit" );

        return receive_pos;
    }

    dummy_log_info( MODULENAME, "on_receive: received '%s'", buffer + receive_pos );

    if( buffer_size + recv_buffer_.size() >= RECV_BUFFER_SIZE )
    {
        // ERROR: cannot accept new data

        dummy_log_error( MODULENAME, "on_receive: recv buffer overflow, curr size %d, new data size %d, MAX SIZE %d",
                recv_buffer_.size(), buffer_size, RECV_BUFFER_SIZE );

        send( "ERROR: recv buffer overflow, closing connection" );

        // explicitly close the connection
        close_async();

        return buffer_size;
    }

    recv_buffer_.append( buffer, buffer_size );

    std::string::size_type eom_pos  = recv_buffer_.find( eom );

    if( eom_pos != std::string::npos )
    {
        // got complete string with EOM marker

        std::string msg = recv_buffer_.substr( 0, eom_pos );

        dummy_log_info( MODULENAME, "on_receive: got complete message: %d: '%s'", msg.size(), msg.c_str() );

        // copy the rest into the front
        recv_buffer_    = recv_buffer_.substr( eom_pos + eom.size() );

        std::string reply = handler_.handle( msg );

        dummy_log_info( MODULENAME, "on_receive: sending response '%s'", reply.c_str() );

        send( reply );

        // explicitly close the connection
        close_async();

        return buffer_size;
    }

    // in case of error close the service and disconnect the client
    if( error )
        close();

    // update read position
    size_t read_pos = buffer_size;

    dummy_log_trace( MODULENAME, "on_receive: exit" );

    return read_pos;
}

NAMESPACE_SERVER_CORE_END
