/*

Server.

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

// $Revision: 1770 $ $Date:: 2015-05-21 #$ $Author: serge $

#include "server.h"             // self
#include "service.h"            // Service
#include "../utils/dummy_logger.h"  // dummy_log
#include "../utils/mutex_helper.h"  // MUTEX_SCOPE_LOCK

#define MODULENAME      "server_core::Server"

NAMESPACE_SERVER_CORE_START

Server::Server():
    handler_( 0L )
{
}

bool Server::init(
        const Config    & cfg,
        IHandler        * handler )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    if( !handler )
        return false;

    bool b = tcpserv::Server::init( cfg );
    if( !b )
        return false;

    handler_    = handler;

    dummy_log_info( MODULENAME, "init: ok" );

    return true;
}


tcpserv::ServicePtr Server::create_service( boost::asio::ip::tcp::socket* socket )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    if( !is_inited__() )
    {
        dummy_log_error( MODULENAME, "create_service: not inited" );

        return tcpserv::ServicePtr();
    }

    tcpserv::ServicePtr s( new Service( this, & get_io_service(), socket, *handler_ ) );
    s->get_receive_buffer().reset( 100 );
    return s;
}

bool Server::is_inited__() const
{
    return handler_ ? true : false;
}


// interface threcon::IControllable
bool Server::shutdown()
{
    dummy_log_debug( MODULENAME, "shutdown()" );

    tcpserv::Server::shutdown( 0 );

    return true;
}


NAMESPACE_SERVER_CORE_END
