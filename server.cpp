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

// $Revision: 6658 $ $Date:: 2017-04-18 #$ $Author: serge $

#include "server.h"             // self
#include "service.h"            // Service
#include "../utils/dummy_logger.h"  // dummy_log
#include "../utils/mutex_helper.h"  // MUTEX_SCOPE_LOCK

NAMESPACE_SERVER_CORE_START

Server::Server():
    log_id_( 0 ),
    log_id_service_( 0 ),
    handler_( 0L )
{
}

bool Server::init(
        const Config    & cfg,
        uint32_t        log_id,
        uint32_t        log_id_service,
        IHandler        * handler )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    if( !handler )
        return false;


    bool b = tcpserv::Server::init( cfg );
    if( !b )
        return false;

    log_id_             = log_id;
    log_id_service_     = log_id_service;
    handler_            = handler;

    dummy_log_info( log_id_, "init: ok" );

    return true;
}


tcpserv::ServicePtr Server::create_service( boost::asio::ip::tcp::socket* socket )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    if( !is_inited__() )
    {
        dummy_log_error( log_id_, "create_service: not inited" );

        return tcpserv::ServicePtr();
    }

    tcpserv::ServicePtr s( new Service( this, & get_io_service(), socket, *handler_, log_id_service_ ) );
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
    dummy_log_debug( log_id_, "shutdown()" );

    tcpserv::Server::shutdown( 0 );

    return true;
}


NAMESPACE_SERVER_CORE_END
