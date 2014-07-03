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

// $Id: server.h 679 2014-07-02 16:51:01Z serge $

#include <boost/thread.hpp>         // boost::mutex

#include "../tcpserv/server.h"  // Server, ServicePtr
#include "../utils/types.h"     // uint16, uint32

#include "namespace_lib.h"      // NAMESPACE_SERVER_CORE_START

NAMESPACE_SERVER_CORE_START

class IHandler;

class Server: protected tcpserv::Server
{
public:
    struct Config
    {
        uint16          port;
        uint32          max_threads;
        uint32          max_clients;
    };

public:

    Server();

    bool init(
            const Config    & cfg,
            IHandler        * handler );

    virtual tcpserv::ServicePtr create_service( boost::asio::ip::tcp::socket* socket );

    void start_listen();

    void thread_func();

    void shutdown( uint32 n, uint32 k );

    void join_client_threads();

private:

    bool is_inited__() const;

private:
    mutable boost::mutex        mutex_;

    boost::thread   broadcast_thread_;

    Config          cfg_;
    IHandler        * handler_;

};


NAMESPACE_SERVER_CORE_END
