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

// $Id: server.cpp 679 2014-07-02 16:51:01Z serge $

#include "../tcpserv/server.h"
#include "../tcpserv/service.h"

#include "server.h"             // self
#include "service.h"            // Service
#include "../utils/dummy_logger.h"  // dummy_log
#include "../utils/wrap_mutex.h"    // SCOPE_LOCK

#define MODULENAME      "core::Server"

NAMESPACE_SERVER_CORE_START

Server::Server():
    handler_( 0L )
{
}

bool Server::init(
        const Config    & cfg,
        IHandler        * handler )
{
    SCOPE_LOCK( mutex_ );

    if( !cfg.port || !cfg.max_threads || !cfg.max_clients || !handler )
        return false;

    cfg_        = cfg;
    handler_    = handler;

    return true;
}


tcpserv::ServicePtr Server::create_service( boost::asio::ip::tcp::socket* socket )
{
    SCOPE_LOCK( mutex_ );

    if( !is_inited__() )
    {
        dummy_log_error( MODULENAME, "create_service: not inited" );

        return tcpserv::ServicePtr();
    }

    tcpserv::ServicePtr s( new Service( this, socket, *handler_ ) );
    s->get_receive_buffer().reset( 100 );
    return s;
}

void Server::start_listen()
{
    SCOPE_LOCK( mutex_ );

    if( !is_inited__() )
    {
        dummy_log_error( MODULENAME, "start_listen: not inited" );

        return;
    }

    tcpserv::Server::start_listen( cfg_.port, cfg_.max_threads, cfg_.max_clients );
}

bool Server::is_inited__() const
{
    return handler_ ? true : false;
}

void Server::thread_func()
{
    dummy_log_info( MODULENAME, "thread_func: started" );

    bool should_run    = true;
    while( should_run )
    {
        THREAD_SLEEP_MS( 3 );
    }

    tcpserv::Server::join();

    dummy_log_info( MODULENAME, "thread_func: ended" );
}

void Server::shutdown( uint32 n, uint32 k )
{
    tcpserv::Server::shutdown( n, k );
}

void Server::join_client_threads()
{
    tcpserv::Server::join();
}


NAMESPACE_SERVER_CORE_END
